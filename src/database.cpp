/******************************************************************************
 * database.cpp : wrapper for database interactions
 * ****************************************************************************
 * Copyright (C) 2016 Jalen Adams
 *
 * Authors: Jalen Adams <jalenkadams@gmail.com>
 *
 * This file is part of Bookmarks.
 *
 * Bookmarks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bookmarks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bookmarks. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "database.h"
#include <QFileInfo>
#include <QtDebug>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTextStream>

Database::Database(QString filename)
{
    QFileInfo dbFileInfo;
    dbFileInfo.setFile(filename);

    if (!dbFileInfo.exists()) { // create the file
        qDebug() << "Creating database file at " + filename;

        QFile dbFile;
        dbFile.setFileName(filename);
        dbFile.open(QIODevice::ReadWrite);
        if (!dbFile.exists()) {
            qCritical() << "Failed to create the database file";
            return;
        }
        dbFile.close();
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    db.open();

    // set up the database model
    model = new QSqlTableModel();

    QSettings settings;
    settings.beginGroup("Database");
    model->setTable(settings.value("default_category").toString());
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    // TODO: Set these to change depending on what table is set
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Title"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Completed"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Ongoing?"));
}

Database::~Database()
{
    if (db.open()) {
        db.close();
    }

    delete model;
}

void Database::close()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool Database::executeSqlScript(QFile &script)
{
    if (!script.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open script file: " + script.fileName();
        return false;
    }

    QTextStream inStream(&script);
    QString sqlStatement = "";
    QSqlQuery query(db);

    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        // ignore comments and blank lines
        if (line.startsWith("--") || line.length() == 0) {
            continue;
        }

        sqlStatement += line;
        if (sqlStatement.endsWith(";")) {
            // remove semicolon, since QSqlQuery adds them automatically
            sqlStatement.chop(1);
            if (query.prepare(sqlStatement)) {
                query.exec();
                sqlStatement = "";
            }
            else {
                qDebug() << "Error executing SQL script.";
                return false;
            }
        }
    }
    script.close();
    return true;
}

// Add a new show to the database model
void Database::addShow(QString title, int watched, int total, bool ongoing)
{
    QSqlQuery query(db);

    query.prepare("INSERT INTO show VALUES (:id, :title, :episodes_watched, :episodes_toal, ongoing)");
    query.bindValue(":id", model->rowCount());
    query.bindValue(":title", title);
    query.bindValue("episodes_watched", watched);
    query.bindValue("episodes_total", total);
    query.bindValue(":ongoing", ongoing);

    model->insertRecord(-1, query.record());
}

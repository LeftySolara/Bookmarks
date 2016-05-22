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
#include <QFile>
#include <QtDebug>
#include <QSettings>

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

    db.setDatabaseName(filename);
}

Database::~Database()
{
    if (db.open()) {
        db.close();
    }

//    delete model;
//    delete view;
}

void Database::close()
{
    if (db.isOpen()) {
        db.close();
    }
}

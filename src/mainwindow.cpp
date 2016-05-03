/******************************************************************************
 * mainwindow.cpp : the main GUI window for the application
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"

#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QSqlQuery>

#define DATABASE_NAME "bookmarks.sqlite"
#define DATABASE_INIT_SCRIPT "../scripts/db_init.sql"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName("Jalen Adams");
    QCoreApplication::setApplicationName("Bookmarks");
    QCoreApplication::setOrganizationDomain("jalenkadams.me");

    if (!logger::setup()) {
        qDebug() << "Could not set up logging function";
    }

    qInfo() << "Starting new application session...";
    errmsg = new QErrorMessage(this);

    if (!settingsExist()) {
        qInfo() << "No settings found. Applying defaults...";
        applyDefaultSettings();
    }

    createDatabase();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    db.close();

    delete ui;
    delete errmsg;
}

// Check for a config file in the correct location (user scope).
// On Unix, this is $HOME/.config
// On Windows, it's %APPDATA%
bool MainWindow::settingsExist()
{
    QSettings settings;
    QFileInfo settings_info(settings.fileName());
    return settings_info.exists();
}

void MainWindow::applyDefaultSettings()
{
    QSettings settings;

    // Remove previous settings
    QStringList keys = settings.allKeys();
    for (QString key : keys) {
        settings.remove(key);
    }

    // Database settings
    QFileInfo settings_info(settings.fileName());
    QString settingsPath = settings_info.fileName();
    QString databasePath = settings.fileName().replace(settingsPath, DATABASE_NAME);

    settings.beginGroup("database");
    settings.setValue("path", databasePath);
    settings.endGroup();
}

// Create the application database in the location specified in the user's settings.
// By default, the location is $HOME/.config (on Unix) or %APPDATA% (on Windows).
// If the database already exists, this method does nothing.
void MainWindow::createDatabase()
{
    QSettings settings;
    QFile databaseFile;

    settings.beginGroup("database");
    QString databasePath = settings.value("path").toString();
    databaseFile.setFileName(databasePath);

    if (databaseFile.exists()) {
        return;
    }

    // Create the database file
    qDebug() << "Creating database file at " + databasePath + "...";
    databaseFile.open(QIODevice::ReadWrite);
    if (!databaseFile.exists()) {
        qCritical() << "Could not create database file";
        errmsg->showMessage("Error creating database file.");
        return;
    }
    databaseFile.close();

    // Create a connection to the database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);

    if (!db.open()) {
        qCritical() << "Could not open database file";
        errmsg->showMessage("Error opening database file.");
        QCoreApplication::exit();
    }

    // read a sql script to initialize the database
    if (!execSqlScript(DATABASE_INIT_SCRIPT)) {
        qDebug() << "Error reading sql script";
    }

    settings.endGroup();
    qInfo() << "Database created successfully";
}

// Read a given SQL script and execute each statement on the application database.
// If execution is successful, returns true. Otherwise, returns false.
bool MainWindow::execSqlScript(QString filename)
{
    QSqlQuery *qry = new QSqlQuery(db);
    QFile *script = new QFile(this);
    script->setFileName(filename);

    if (!script->open(QIODevice::ReadOnly)) {
        return false;
    }

    QTextStream inStream(script);
    QString sqlStatement = "";

    while (!inStream.atEnd())
    {
        QString line = inStream.readLine();

        if (line.startsWith("--") || line.length() == 0) { // ignore comments and blank lines
            continue;
        }

        sqlStatement += line;
        if (sqlStatement.endsWith(";")) {
            // remove semicolon at end of line, since QSqlQuery adds them automatically
            sqlStatement.chop(1);
            if (qry->prepare(sqlStatement)) {
                qry->exec();
                sqlStatement = "";
            }
            else {
              return false;
            }
        }
    }
    script->close();

    delete script;
    delete qry;

    return true;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

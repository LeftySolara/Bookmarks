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
#include "dialogaddmedia.h"
#include "logger.h"

#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QSqlQuery>

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

#define DATABASE_NAME "bookmarks.sqlite"
#define DATABASE_INIT_SCRIPT "../scripts/db_init.sql"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName("Jalen Adams");
    QCoreApplication::setApplicationName("Bookmarks");
    QCoreApplication::setOrganizationDomain("jalenkadams.me");

    ui->setupUi(this);

    if (!logger::setup()) {
        qDebug() << "Could not set up logging function";
    }
    qInfo() << "Starting new application session...";
    errmsg = new QErrorMessage(this);

    if (!settingsExist()) {
        qInfo() << "No settings found. Applying defaults...";
        applyDefaultSettings();
    }

    QSettings settings;
    settings.beginGroup("Database");
    db = new Database(settings.value("path").toString());

    // initialize the database if necessary
    // TODO: write scripts to update database structure without deleting everything
    if (db->versionMajor() != VERSION_MAJOR || db->versionMinor() != VERSION_MINOR) {
        QFile script;
        script.setFileName(DATABASE_INIT_SCRIPT);
        if (!db->executeSqlScript(script)) {
            qCritical() << "Failed to initialize database";
            errmsg->showMessage("Failed to initialize database.");
            QCoreApplication::exit();
        }
    }
    db->connect();
    settings.endGroup();
}

MainWindow::~MainWindow()
{
    db->close();

    delete ui;
    delete errmsg;
    delete db;
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

    settings.beginGroup("Database");
    settings.setValue("path", databasePath);
    settings.setValue("default_category", "show");
    settings.endGroup();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_actionAdd_show_triggered()
{
    DialogAddMedia *dialog = new DialogAddMedia();
    dialog->exec();
}

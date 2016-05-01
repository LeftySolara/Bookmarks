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
#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QFileInfo>

#define DATABASE_NAME "bookmarks.sqlite"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName("JalenAdams");
    QCoreApplication::setApplicationName("Bookmarks");
    QCoreApplication::setOrganizationDomain("jalenkadams.me");

    if (!settingsExist()) {
        applyDefaultSettings();
    }

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

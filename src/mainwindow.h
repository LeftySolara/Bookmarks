/******************************************************************************
 * mainwondow.h : the main GUI window for the application
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QErrorMessage>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool settingsExist();
    void applyDefaultSettings();

    void createDatabase();
    bool execSqlScript(QString filename);

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionAdd_show_triggered();

private:
    Ui::MainWindow *ui;
    QErrorMessage *errmsg;
    QSqlDatabase db;
    QSqlTableModel *tableModel;
    QTableView *tableView;
};

#endif // MAINWINDOW_H

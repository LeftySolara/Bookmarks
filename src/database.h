/******************************************************************************
 * database.h : wrapper for database interactions
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

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QFile>

class Database
{
public:
    Database(QString filename);
    ~Database();

    bool connect() { return db.open(); }
    void close();
    bool isValid() { return db.isValid(); }
    bool executeSqlScript(QFile script);

    int versionMajor();
    int versionMinor();

//    addShow(QString title, int watched, int total, bool ongoing);
//    addManga(QString title, int read, int total, bool ongoing);
//    removeEntry(QString tableName, int id);

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QTableView *view;
};

#endif // DATABASE_H

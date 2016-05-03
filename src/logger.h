/******************************************************************************
 * logger.h : namespace for functions that handle application logging
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bookmarks.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <QtMsgHandler>
#include <QDateTime>
#include <QFile>
#include <stdio.h>

namespace logger
{
extern QDateTime currentDateTime;
extern QString dataPath;
extern QFile logFile;

bool setup();
void writeMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
}

#endif // LOGGER_H

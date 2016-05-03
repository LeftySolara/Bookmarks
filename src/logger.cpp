/******************************************************************************
 * logger.cpp : namespace for functions that handle application logging
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

#include "logger.h"
#include <QDir>
#include <QTextStream>
#include <QtDebug>
#include <QStandardPaths>
#include <QTime>
#include <QDate>

namespace logger
{
QDateTime currentDateTime;
QString dataPath;
QFile logFile;

// Create directory and file for logs if none exist
bool setup()
{
    QDir dir;
    dataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if (!dir.mkpath(dataPath)) {
        return false;
    }

    logFile.setFileName(dataPath + "/log");
    logFile.open(QIODevice::Append);

    qInstallMessageHandler(writeMessage);
    currentDateTime.setDate(QDate::currentDate());

    return true;
}

void writeMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QTextStream out(&logFile);
    currentDateTime.setTime(QTime::currentTime());

    switch (type) {
    case QtDebugMsg:
        out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " Debug: " << localMsg.constData() << " (" << context.file
            << ":" << context.line << ", " << context.function << ")\n";
        break;
    case QtInfoMsg:
        out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " Info: " << localMsg.constData() << " (" << context.file
            << ":" << context.line << ", " << context.function << ")\n";
        break;
    case QtWarningMsg:
        out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " Warning: " << localMsg.constData() << " (" << context.file
            << ":" << context.line << ", " << context.function << ")\n";
        break;
    case QtCriticalMsg:
        out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " Critical: " << localMsg.constData() << " (" << context.file
            << ":" << context.line << ", " << context.function << ")\n";
        break;
    case QtFatalMsg:
        out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " Fatal: " << localMsg.constData() << " (" << context.file
            << ":" << context.line << ", " << context.function << ")\n";
    }
}

}

/******************************************************************************
 * dialogaddmedia.cpp : dialog for adding a new show to the database
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

#include "dialogaddmedia.h"
#include "ui_dialogaddmedia.h"

DialogAddMedia::DialogAddMedia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddMedia)
{
    setupLayoutInfo();
    this->setLayout(layoutInfo);

    ui->setupUi(this);
}

DialogAddMedia::~DialogAddMedia()
{
    delete lineEditTitle;
    delete spinBoxEpisodesWatched;
    delete spinBoxEpisodesTotal;
    delete comboBoxStatus;

    delete layoutInfo;
    delete ui;
}

void DialogAddMedia::setupLayoutInfo()
{
    layoutInfo = new QFormLayout();
    lineEditTitle = new QLineEdit();
    spinBoxEpisodesWatched = new QSpinBox();
    spinBoxEpisodesTotal = new QSpinBox();
    comboBoxStatus = new QComboBox();

    comboBoxStatus->addItem("Ongoing");
    comboBoxStatus->addItem("Completed");

    layoutInfo->addRow("Title", lineEditTitle);
    layoutInfo->addRow("Episodes Watched", spinBoxEpisodesWatched);
    layoutInfo->addRow("Total Episodes", spinBoxEpisodesTotal);
    layoutInfo->addRow("Status", comboBoxStatus);
}

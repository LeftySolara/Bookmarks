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
#include <QSize>
#include <QFileDialog>
#include "QDebug"

DialogAddMedia::DialogAddMedia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddMedia)
{
    setupLayoutButtons();
    setupLayoutInfo();

    layoutMaster = new QVBoxLayout();
    layoutMaster->addLayout(layoutInfo);
    layoutMaster->addSpacing(15);
    layoutMaster->addLayout(layoutButtons);
    layoutMaster->setSizeConstraint(QVBoxLayout::SetFixedSize);
    this->setLayout(layoutMaster);

    ui->setupUi(this);
}

DialogAddMedia::~DialogAddMedia()
{
    delete lineEditTitle;
    delete spinBoxEpisodesWatched;
    delete spinBoxEpisodesTotal;
    delete comboBoxStatus;

    delete layoutInfo;
    delete layoutButtons;
    delete layoutMaster;
    delete ui;
}

// Set up the right half of the dialog. Just a basic input form.
void DialogAddMedia::setupLayoutInfo()
{
    layoutInfo = new QFormLayout();
    layoutInfo->setFormAlignment(Qt::AlignCenter);
    layoutInfo->setSizeConstraint(QFormLayout::SetFixedSize);

    lineEditTitle = new QLineEdit();
    lineEditTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    spinBoxEpisodesWatched = new QSpinBox();
    spinBoxEpisodesWatched->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    spinBoxEpisodesTotal = new QSpinBox();
    spinBoxEpisodesTotal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    comboBoxStatus = new QComboBox();
    comboBoxStatus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    comboBoxStatus->addItem("Ongoing");
    comboBoxStatus->addItem("Completed");

    layoutInfo->addRow("Title", lineEditTitle);
    layoutInfo->addRow("Episodes Watched", spinBoxEpisodesWatched);
    layoutInfo->addRow("Total Episodes", spinBoxEpisodesTotal);
    layoutInfo->addRow("Status", comboBoxStatus);
}

void DialogAddMedia::setupLayoutButtons()
{
    layoutButtons = new QHBoxLayout();
    buttonAccept = new QPushButton("Accept");
    buttonReject = new QPushButton("Cancel");

    buttonAccept->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonReject->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layoutButtons->addWidget(buttonAccept);
    layoutButtons->addWidget(buttonReject);

    connect(buttonAccept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonReject, SIGNAL(clicked()), this, SLOT(reject()));
}

QString DialogAddMedia::title()
{
    return lineEditTitle->text();
}

int DialogAddMedia::num_completed()
{
    return spinBoxEpisodesWatched->value();
}

int DialogAddMedia::num_total()
{
    return spinBoxEpisodesTotal->value();
}

bool DialogAddMedia::ongoing()
{
    return comboBoxStatus->currentText().toLower() == "ongoing";
}

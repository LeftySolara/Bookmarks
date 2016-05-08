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

DialogAddMedia::DialogAddMedia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddMedia)
{
    setupLayoutInfo();
    setupLayoutArtwork();

    layoutMaster = new QHBoxLayout();
    layoutMaster->addLayout(layoutArtwork);
    layoutMaster->addLayout(layoutInfo);
    layoutMaster->setSizeConstraint(QHBoxLayout::SetFixedSize);
    this->setLayout(layoutMaster);

    ui->setupUi(this);
}

DialogAddMedia::~DialogAddMedia()
{
    delete lineEditTitle;
    delete spinBoxEpisodesWatched;
    delete spinBoxEpisodesTotal;
    delete comboBoxStatus;
    delete artwork;
    delete artLabel;
    delete buttonUploadArt;
    delete buttonDownloadArt;

    delete layoutInfo;
    delete layoutArtwork;
    delete layoutMaster;
    delete ui;
}

// Set up the right half of the dialog. Just a basic input form.
void DialogAddMedia::setupLayoutInfo()
{
    layoutInfo = new QFormLayout();
    layoutInfo->setSizeConstraint(QFormLayout::SetFixedSize);

    lineEditTitle = new QLineEdit();
    lineEditTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    spinBoxEpisodesWatched = new QSpinBox();
    spinBoxEpisodesWatched->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    spinBoxEpisodesTotal = new QSpinBox();
    spinBoxEpisodesTotal->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    comboBoxStatus = new QComboBox();
    comboBoxStatus->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    comboBoxStatus->addItem("Ongoing");
    comboBoxStatus->addItem("Completed");

    layoutInfo->addRow("Title", lineEditTitle);
    layoutInfo->addRow("Episodes Watched", spinBoxEpisodesWatched);
    layoutInfo->addRow("Total Episodes", spinBoxEpisodesTotal);
    layoutInfo->addRow("Status", comboBoxStatus);
}

// Set up the left half of the dialog. Will contain preview artwork for the series, a button for
// choosing art from a local file, and a button for downloading art from the web.
void DialogAddMedia::setupLayoutArtwork()
{
    layoutArtwork = new QVBoxLayout();
    layoutArtwork->setSizeConstraint(QVBoxLayout::SetFixedSize);

    buttonUploadArt = new QPushButton("Choose from file");
    buttonDownloadArt = new QPushButton("Download from web");

    connect(buttonUploadArt, SIGNAL(clicked()), this, SLOT(uploadArtwork()));

    QSize buttonSize(150, 40);
    buttonUploadArt->setFixedSize(buttonSize);
    buttonDownloadArt->setFixedSize(buttonSize);

    artwork = new QImage(":/images/art_placeholder");
    artLabel = new QLabel();

    artLabel->setPixmap(QPixmap::fromImage(artwork->scaledToWidth(buttonDownloadArt->width())));
    artLabel->setFixedSize(buttonSize.width(), 540);

    layoutArtwork->addWidget(artLabel);
    layoutArtwork->addWidget(buttonUploadArt);
    layoutArtwork->addWidget(buttonDownloadArt);
}

void DialogAddMedia::uploadArtwork()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "~/", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage art(filename);

    artLabel->setPixmap(QPixmap::fromImage(art.scaledToWidth(buttonUploadArt->width())));
}

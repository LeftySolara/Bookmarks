/******************************************************************************
 * dialogaddmedia.h : dialog for adding a new show to the database
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

#ifndef DIALOGADDMEDIA_H
#define DIALOGADDMEDIA_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class DialogAddMedia;
}

class DialogAddMedia : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddMedia(QWidget *parent = 0);
    ~DialogAddMedia();

    void setupLayoutInfo();
    void setupLayoutButtons();

    QString title() { return lineEditTitle->text(); }
    int num_completed() { return spinBoxEpisodesWatched->value(); }
    int num_total() { return spinBoxEpisodesTotal->value(); }
    bool ongoing() { return true; }

private:
    Ui::DialogAddMedia *ui;

   QVBoxLayout *layoutMaster;
   QFormLayout *layoutInfo;
   QHBoxLayout *layoutButtons;

   QLineEdit *lineEditTitle;
   QSpinBox *spinBoxEpisodesWatched;
   QSpinBox *spinBoxEpisodesTotal;
   QComboBox *comboBoxStatus;

   QPushButton *buttonAccept;
   QPushButton *buttonReject;
};

#endif // DIALOGADDMEDIA_H

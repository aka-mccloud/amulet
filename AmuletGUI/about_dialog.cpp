/**************************************************************************
 *                                                                        *
 *  Copyright (C) 2012 by Yura Ivanov <yura.i1507@gmail.com>              *
 *                                                                        *
 *  This file is part of Amulet audio converter.                          *
 *                                                                        *
 *  Amulet is free software: you can redistribute it and/or modify        *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  Amulet is distributed in the hope that it will be useful,             *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with Amulet.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                        *
 **************************************************************************/

#include <QPixmap>

#include "about_dialog.hpp"

AboutDialog::AboutDialog(QWidget * parent)
    : QDialog(parent)
{
    ui = new Ui::AboutDialog();
    ui->setupUi(this);
    QPixmap pix(":/icons/amulet.png");
    this->ui->aboutLogoLbl->setPixmap(pix);
    this->ui->aboutTextLbl->setText(
                tr("<b>Amulet</b><br>Simple audio converter.<br>Version ") + "2.0 alpha 1" +
                tr("<br><br>Authors:<br>Yura Ivanov <a href=\"mailto:yura.i1507@gmail.com\">yura.i1507@gmail.com</a>") +
                tr("<br><br><a href=\"http://www.gnu.org/licenses/gpl-2.0.html\">License: GNU General Public License, version 2"));
}

AboutDialog::~AboutDialog() {
    delete ui;
}

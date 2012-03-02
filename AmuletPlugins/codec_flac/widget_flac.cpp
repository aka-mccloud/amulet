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

#include "widget_flac.hpp"
#include "ui_widget_flac.h"

WidgetFlac::WidgetFlac() :
    ui(new Ui::WidgetFlac) {
    ui->setupUi(this);
    ui->sampleRateBox->addItems(QString("48000 44100 22050").split(' '));
}

WidgetFlac::~WidgetFlac() {
    delete ui;
}

void WidgetFlac::on_qualityEdit_valueChanged(int value) {
    ui->qualitySlider->setValue(value);
}

void WidgetFlac::on_qualitySlider_valueChanged(int value) {
    ui->qualityEdit->setValue(value);
}

CodecProperties WidgetFlac::getProperties() {
    CodecProperties properties;
    properties[CodecProperties::SAMPLERATE] = ui->sampleRateBox->currentText();

    return properties;
}

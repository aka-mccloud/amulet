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

#include "widget_lame.hpp"
#include "ui_widget_lame.h"

WidgetLame::WidgetLame() :
    ui(new Ui::WidgetLame) {
    ui->setupUi(this);
    ui->bitrateBox->addItems(QString("32 40 48 56 64 80 96 112 128 160 192 224 256 320").split(' '));
}

WidgetLame::~WidgetLame() {
    delete ui;
}

void WidgetLame::on_qualityEdit_valueChanged(int value) {
    ui->qualitySlider->setValue(value);
}

void WidgetLame::on_qualitySlider_valueChanged(int value) {
    ui->qualityEdit->setValue(value);
}

CodecProperties WidgetLame::getProperties() {
    CodecProperties properties;
    properties[CodecProperties::BITRATE] = ui->bitrateBox->currentText();
    properties[CodecProperties::SAMPLERATE] = ui->sampleRateBox->currentText();
    properties[CodecProperties::LOWPASS] = "22";

    return properties;
}

void WidgetLame::on_selectBox_currentIndexChanged(int index) {
    ui->stackedWidget->setCurrentIndex(index);
}

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

#include "encoder_lame.hpp"

EncoderLame::EncoderLame(QObject * parent) :
    QObject(parent) {
    options[CodecProperties::BITRATE] = "-b";
    options[CodecProperties::SAMPLERATE] = "--resample";
    options[CodecProperties::LOWPASS] = "--lowpass";

    process = new QProcess(this);
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

EncoderLame::~EncoderLame() {
    delete process;
}

void EncoderLame::setOutputFile(const QString & fileName) {
    outputFile = fileName;
}

void EncoderLame::setProperties(const CodecProperties & props) {
    args += props.toStringList(options);
}

QProcess * EncoderLame::getProcessInstance() {

    return process;
}

QObject * EncoderLame::getObject() {

    return this;
}

void EncoderLame::start() {
    if (inputFile.isEmpty()) {
        args += QString("-");
    } else {
        args += inputFile;
    }
    args += outputFile;

    process->start(coderName, args);
}

void EncoderLame::stop() {
    process->terminate();
}

void EncoderLame::finished(int) {
    emit finished();
}

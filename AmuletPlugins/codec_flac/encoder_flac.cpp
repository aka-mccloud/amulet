/**************************************************************************
 *                                                                        *
 *  Copyright (C) 2020 by Yurii Ivanov <yivanov00@gmail.com>              *
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

#include "encoder_flac.hpp"

EncoderFlac::EncoderFlac(QObject * parent)
    : QObject(parent)
{
    options[CodecProperties::SAMPLERATE] = "--sample-rate=";

    process = new QProcess(this);
    connect(process,
            SIGNAL(finished(int)),
            SLOT(finished(int)));
}

EncoderFlac::~EncoderFlac()
{
    delete process;
}

void EncoderFlac::setOutputFile(const QString & fileName)
{
    outputFile = fileName;
}

void EncoderFlac::setProperties(const CodecProperties & props)
{
    //args += props.toStringList(options);
}

QProcess * EncoderFlac::getProcessInstance()
{
    return process;
}

QObject * EncoderFlac::getObject()
{
    return this;
}

void EncoderFlac::start()
{
    if (inputFile.isEmpty())
        args += QString("-");
    else
        args += inputFile;

    args += QString("-o");
    args += outputFile;

    process->start(coderName, args);
}

void EncoderFlac::stop()
{
    terminated = true;
    process->terminate();
}

void EncoderFlac::finished(int)
{
    if (!terminated)
        emit finished();
}

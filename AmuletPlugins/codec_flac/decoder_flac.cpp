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

#include <QDebug>

#include "decoder_flac.hpp"

DecoderFlac::DecoderFlac(QObject * parent)
    : QObject(parent), terminated(false)
{
    args += QString("-d");
    process = new QProcess();

    connect(process,
            SIGNAL(readyReadStandardError()),
            SLOT(calculateProgress()));
    connect(process,
            SIGNAL(finished(int)),
            SLOT(finished(int)));
}

DecoderFlac::~DecoderFlac()
{
    delete process;
}

void DecoderFlac::calculateProgress()
{
    QString out(process->readAllStandardError());
    QRegExp rx("([\\d]{1,3})% complete");

    if (rx.indexIn(out) >= 0) {
        completed = rx.cap(1).toInt();

        emit progress(completed);
    }
}

void DecoderFlac::setInputFile(const QString & fileName)
{
    inputFile = fileName;
}

void DecoderFlac::setOutputFile(const QString & fileName)
{
    outputFile = fileName;
}

QProcess * DecoderFlac::getProcessInstance()
{
    return process;
}

QObject * DecoderFlac::getObject()
{
    return this;
}

void DecoderFlac::start()
{
    args += inputFile;
    if (outputFile.isEmpty())
        args += QString("-c");
    else
        args += outputFile;

    process->start(decoderName, args);
}

void DecoderFlac::stop()
{
    terminated = true;
    process->terminate();
}

void DecoderFlac::finished(int)
{
    if (!terminated)
        emit finished();
}

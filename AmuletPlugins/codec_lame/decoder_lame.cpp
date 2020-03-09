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

#include "decoder_lame.hpp"

DecoderLame::DecoderLame(QObject * parent)
    : QObject(parent), terminated(false)
{
    args += QString("--decode");
    process = new QProcess();

    connect(process,
            SIGNAL(readyReadStandardError()),
            SLOT(calculateProgress()));
    connect(process,
            SIGNAL(finished(int)),
            SLOT(finished(int)));
}

DecoderLame::~DecoderLame()
{
    delete process;
}

void DecoderLame::calculateProgress()
{
    QString out(process->readAllStandardError());
    QRegExp rx("Frame#.*([\\d]+)/([\\d]+)");

    if (rx.indexIn(out) >= 0) {
        completed = rx.cap(1).toInt() / rx.cap(2).toInt() * 100;

        emit progress(completed);
    }
}

void DecoderLame::setInputFile(const QString & fileName)
{
    inputFile = fileName;
}

void DecoderLame::setOutputFile(const QString & fileName)
{
    outputFile = fileName;
}

QProcess * DecoderLame::getProcessInstance()
{
    return process;
}

QObject * DecoderLame::getObject()
{
    return this;
}

void DecoderLame::start()
{
    args += inputFile;
    if (outputFile.isEmpty())
        args += QString("-");
    else
        args += outputFile;

    process->start(decoderName, args);
}

void DecoderLame::stop()
{
    terminated = true;
    process->terminate();
}

void DecoderLame::finished(int)
{
    if (!terminated)
        emit finished();
}

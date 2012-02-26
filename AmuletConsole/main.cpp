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

#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

#include "converter_service.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Queue queue;
    queue.append(QueueItem(QFileInfo("02 - Injection.flac")));
    queue.append(QueueItem(QFileInfo("03 - Ready to Fall.flac")));
    queue.append(QueueItem(QFileInfo("09 - Give It All.flac")));
    queue.append(QueueItem(QFileInfo("12 - The Good Left Undone.flac")));
    QDir outDir(QCoreApplication::applicationDirPath());

    CodecProperties properties;
    properties[CodecProperties::BITRATE] = "320";
    properties[CodecProperties::SAMPLERATE] = "44.1";
    properties[CodecProperties::LOWPASS] = "22";

    ConverterService service(&a);
    //QObject::connect(&service, SIGNAL(finished()), &a, SLOT(quit()));
    service.setCodecProperties(properties);
    service.setMaxThreadCount(3);
    service.setOutDir(outDir);
    service.setQueue(&queue);
    service.start();

    return a.exec();
}

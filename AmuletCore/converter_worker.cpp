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
#include <QFileInfo>
#include <QDir>

#include "converter_worker.hpp"

ConverterWorker::ConverterWorker(QueueItem * queueItem, const QString & targetPath,
                                 const QString & format, IDecoderProcess * decoder,
                                 IEncoderProcess * encoder, QObject * parent)
    : QObject(parent), queueItem(queueItem), decoder(decoder), encoder(encoder), completed(0)
{
    tagData = TagEngine::readFromFile(queueItem->getFile());
    targetFile = replaceTags(targetPath) + "." + format;
    QDir dir(targetFile.section('/', 0, -2));
    if (!dir.exists())
        dir.mkpath(dir.absolutePath());

    decoder->setInputFile(queueItem->getFile().absoluteFilePath());
    encoder->setOutputFile(targetFile);
    this->decoder->getProcessInstance()->setStandardOutputProcess(this->encoder->getProcessInstance());
    connect(this->encoder->getObject(),
            SIGNAL(finished()),
            SLOT(endConvert()));
    connect(this->decoder->getObject(),
            SIGNAL(progress(int)),
            SLOT(progressReady(int)));
}

ConverterWorker::~ConverterWorker()
{
    stop();

    delete decoder;
    delete encoder;
}

QString ConverterWorker::replaceTags(QString path)
{
    QRegExp rx("[$]{1}num[(]{1}(%[\\w]+%),([\\d]+)[)]{1}");
    while (rx.indexIn(path) >= 0) {
         int num = rx.cap(2).toInt();

         if (rx.cap(1) == "%track%")
             path.replace(rx.cap(0), QString("%1").arg(QString::number(tagData->track), num, '0'), Qt::CaseInsensitive);
         else
             path.replace(rx.cap(0), rx.cap(1));
    }

    path.replace("%artist%", tagData->artist, Qt::CaseInsensitive);
    path.replace("%album%", tagData->album, Qt::CaseInsensitive);
    path.replace("%genre%", tagData->genre, Qt::CaseInsensitive);
    path.replace("%track%", QString::number(tagData->track), Qt::CaseInsensitive);
    path.replace("%title%", tagData->title, Qt::CaseInsensitive);
    path.replace("%year%", QString::number(tagData->year), Qt::CaseInsensitive);

    return path;
}

void ConverterWorker::endConvert()
{
    TagEngine::writeToFile(QFileInfo(targetFile), tagData);

    emit finished(this);
}

void ConverterWorker::progressReady(int p)
{
//    qDebug() << p;
    queueItem->setProgress(p);

    emit progress(p);
}

QObject * ConverterWorker::getObject()
{
    return this;
}

void ConverterWorker::start()
{
    decoder->start();
    encoder->start();
}

void ConverterWorker::stop()
{
    decoder->stop();
    encoder->stop();
}

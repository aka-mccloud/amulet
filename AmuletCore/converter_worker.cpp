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

#include <QDebug>
#include <QFileInfo>

#include "converter_worker.hpp"

ConverterWorker::ConverterWorker(const QFileInfo & sourceFile,
                                 const QString & targetPath,
                                 const QString & format,
                                 IDecoderProcess * decoder,
                                 IEncoderProcess * encoder,
                                 QObject * parent) :
    QObject(parent),
    decoder(decoder),
    encoder(encoder),
    completed(0) {
    tagData = TagEngine::readFromFile(sourceFile);
    targetFile = targetPath + "/" + sourceFile.completeBaseName() + "." + format;
    decoder->setInputFile(sourceFile.absoluteFilePath());
    encoder->setOutputFile(targetFile);
    this->decoder->getProcessInstance()->setStandardOutputProcess(this->encoder->getProcessInstance());
    connect(this->encoder->getObject(), SIGNAL(finished()),
            SLOT(endConvert()));
    connect(this->decoder->getObject(), SIGNAL(progress(int)),
            SLOT(progressReady(int)));
}

ConverterWorker::~ConverterWorker() {
    stop();
    delete decoder;
    delete encoder;
}

QObject * ConverterWorker::getObject() {

    return this;
}

void ConverterWorker::start() {
    decoder->start();
    encoder->start();
}

void ConverterWorker::stop() {
    decoder->stop();
    encoder->stop();
}

void ConverterWorker::endConvert() {
    TagEngine::writeToFile(QFileInfo(targetFile), tagData);
    emit finished(this);
}

void ConverterWorker::progressReady(int p) {
//    qDebug() << p;
    emit progress(p);
}

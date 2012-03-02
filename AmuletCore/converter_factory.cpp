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

#include <QFileInfo>

#include "converter_factory.hpp"

ConverterFactory::ConverterFactory(QObject * parent) :
    QObject(parent) {
}

ConverterWorker * ConverterFactory::create(QueueItem * item,
                                           const QString & targetPath,
                                           const QString & format,
                                           const CodecProperties & props) {
    ConverterWorker * converterWorker = NULL;

    if (item != NULL) {
        QFileInfo file = item->getFile();
        IDecoderProcess * decoder = codecFactory.getDecoderForType(file.suffix());
        IEncoderProcess * encoder = codecFactory.getEncoderForType(format);

        if ((decoder != NULL) && (encoder != NULL)) {
            QString targetFile = targetPath + "/" +
                    file.completeBaseName() + "." + format;
            decoder->setInputFile(file.absoluteFilePath());
            encoder->setOutputFile(targetFile);
            encoder->setProperties(props);

            converterWorker = new ConverterWorker(decoder, encoder, this);
            connect(converterWorker,
                    SIGNAL(progress(int)),
                    item,
                    SLOT(setPprogress(int)));
        }
    }

    return converterWorker;
}

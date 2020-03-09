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

#include <QFileInfo>

#include "converter_factory.hpp"

ConverterFactory::ConverterFactory(QObject * parent) :
    QObject(parent)
{
    // empty
}

ConverterWorker * ConverterFactory::create(QueueItem * item, const QString & targetPath,
                                           const QString & format, const CodecProperties & props)
{
    ConverterWorker * converterWorker = NULL;

    if (item != NULL) {
        QFileInfo file = item->getFile();
        IDecoderProcess * decoder = codecFactory.getDecoderForType(file.suffix());
        IEncoderProcess * encoder = codecFactory.getEncoderForType(format);

        if ((decoder != NULL) && (encoder != NULL)) {
            encoder->setProperties(props);
            converterWorker = new ConverterWorker(item, targetPath, format,
                                                  decoder, encoder, this);
        }
    }

    return converterWorker;
}


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

#ifndef CONVERTER_FACTORY_HPP
#define CONVERTER_FACTORY_HPP

#include <QObject>
#include <QDir>

#include "codec_factory.hpp"
#include "converter_worker.hpp"
#include "queue_item.hpp"

class ConverterFactory : public QObject {

    Q_OBJECT

private:
    CodecFactory codecFactory;

public:
    explicit ConverterFactory(QObject * parent = 0);
    virtual ~ConverterFactory() {}

    ConverterWorker * create(QueueItem * item,
                             const QDir & outDir,
                             const QString & format,
                             const CodecProperties & props);

};

#endif // CONVERTER_FACTORY_HPP

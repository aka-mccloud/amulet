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

#ifndef CONVERTER_WORKER_HPP
#define CONVERTER_WORKER_HPP

#include <QLinkedList>

#include "queue_item.hpp"
#include "tag_data.hpp"
#include "tag_engine.hpp"
#include "iworker.hpp"
#include "idecoder_process.hpp"
#include "iencoder_process.hpp"

class ConverterWorker : public QObject, public IWorker
{

    Q_OBJECT
    Q_INTERFACES(IWorker)

private:
    QueueItem * queueItem;
    TagData * tagData;
    QString targetFile;
    IDecoderProcess * decoder;
    IEncoderProcess * encoder;
    int completed;
    
    QString replaceTags(QString path);

private slots:
    void endConvert();
    void progressReady(int p);

public:
    explicit ConverterWorker(QueueItem * queueItem, const QString & targetPath,
                             const QString & format, IDecoderProcess * decoder,
                             IEncoderProcess * encoder, QObject * parent = 0);
    virtual ~ConverterWorker();

    QObject * getObject();

public slots:
    void start();
    void stop();

signals:
    void progress(int);
    void finished(IWorker *);

};

#endif // CONVERTER_WORKER_HPP

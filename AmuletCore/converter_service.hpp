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

#ifndef CONVERTER_SERVICE_HPP
#define CONVERTER_SERVICE_HPP

#include <QSettings>
#include <QFileInfo>
#include <QList>
#include <QDir>

#include "AmuletCore_global.hpp"

#include "codec_properties.hpp"
#include "converter_factory.hpp"
#include "worker_pool.hpp"
#include "queue.hpp"

class AMULETCORESHARED_EXPORT ConverterService : public QObject
{

    Q_OBJECT

private:
    CodecProperties properties;
    Queue * queue;
    QString targetPath;
    QString format;
    int threads;
    ConverterFactory factory;
    WorkerPool pool;
    bool running;

private slots:
    void pushNext();
    void updateProgress();

public:
    explicit ConverterService(QObject * parent = 0);
    virtual ~ConverterService();

    void setSettings(const QSettings & settings);
    void setCodecProperties(CodecProperties props);
    void setMaxThreadCount(int maxThreadCount);
    void setOutPath(const QString & targetPath);
    void setQueue(Queue * queue);
    void setOutFormat(const QString & format);
    bool isRunning();

public slots:
    void start();
    void stop();

signals:
    void progressChanged();
    void finished();

};

#endif // CONVERTER_SERVICE_HPP

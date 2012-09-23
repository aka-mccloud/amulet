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

#include <QDesktopServices>
#include <QDebug>

#include "converter_service.hpp"

ConverterService::ConverterService(QObject * parent) :
    QObject(parent),
    threads(1),
    pool(parent),
    running(false) {
    connect(&pool,
            SIGNAL(workerFinished()),
            SLOT(pushNext()));
    connect(&pool,
            SIGNAL(progressChanged()),
            SLOT(updateProgress()));
}

ConverterService::~ConverterService() {
    stop();
}

void ConverterService::setSettings(const QSettings & settings) {
    if (settings.value("Properties/path", false).toBool()) {
        targetPath = settings.value("Properties/target_path",
            QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
    }
    setMaxThreadCount(settings.value("Properties/threads", 1).toInt());
}

void ConverterService::setCodecProperties(CodecProperties props) {
    properties = props;
}

void ConverterService::setMaxThreadCount(int maxThreadCount) {
    threads = maxThreadCount;
}

void ConverterService::setOutPath(const QString & targetPath) {
    this->targetPath = targetPath;
}

void ConverterService::setQueue(Queue * queue) {
    this->queue = queue;
    this->queue->cleanProgress();
}

void ConverterService::setOutFormat(const QString & format) {
    this->format = format;
}

bool ConverterService::isRunning() {
    return running;
}

void ConverterService::pushNext() {
    if (queue->countByStatus(QueueItem::WAITING) != 0) {
        QueueItem * queueItem = queue->getFirstUnprocessed();
        IWorker * worker = factory.create(queueItem, targetPath, format, properties);
        pool.execute(worker);
    } else if (pool.isEmpty()) {
        running = false;
        emit finished();
    }
}

void ConverterService::updateProgress() {
    emit progressChanged();
}

void ConverterService::start() {
    if (!running) {
        running = true;
        for (int i = 0; i < threads; i++) {
            pushNext();
        }
    }
}

void ConverterService::stop() {
    pool.stop();
    running = false;
}

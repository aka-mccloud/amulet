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

#include "worker_pool.hpp"

WorkerPool::WorkerPool(QObject * parent) :
    QObject(parent) {
}

WorkerPool::~WorkerPool() {
    workerList.clear();
}

void WorkerPool::jobFinished(IWorker * worker) {
    if (workerList.removeOne(worker)) {
        worker->getObject()->deleteLater();
        emit workerFinished();
    }
}

void WorkerPool::updateProgress(int) {
    emit progressChanged();
}

void WorkerPool::execute(IWorker * worker) {
    if (worker != NULL) {
        connect(worker->getObject(),
                SIGNAL(finished(IWorker *)),
                SLOT(jobFinished(IWorker *)));
        connect(worker->getObject(),
                SIGNAL(progress(int)),
                SLOT(updateProgress(int)));
        workerList.append(worker);
        worker->start();
    } else {
        emit workerFinished();
    }
}

bool WorkerPool::isEmpty() {

    return workerList.isEmpty();
}

int WorkerPool::size() {

    return workerList.size();
}

void WorkerPool::stop() {
    foreach (IWorker * worker, workerList) {
        worker->stop();
    }
}

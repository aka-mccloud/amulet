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

#include "queue.hpp"

Queue::Queue(QObject * parent) :
    QObject(parent),
    inProgress(0),
    processed(0) {
}

Queue::Queue(Queue & queue) :
    QObject(queue.parent()),
    queue(queue.queue),
    inProgress(queue.inProgress),
    processed(queue.processed) {
}

void Queue::append(QueueItem item) {
//    item.setStatus(QueueItem::WAITING);
    queue.append(item);
}

QLinkedList<QueueItem>::const_iterator Queue::begin() const {

    return queue.begin();
}

void Queue::clear() {
    inProgress = 0;
    processed = 0;
    queue.clear();
}

void Queue::cleanProgress() {
    QLinkedList<QueueItem>::iterator it;

    for (it = queue.begin(); it != queue.end(); ++it) {
        it->setStatus(QueueItem::WAITING);
        it->setProgress(0);
    }
}

double Queue::countProgress() {
    int progress(0);

    foreach (QueueItem item, queue) {
        progress += item.getProgress();
    }

    return progress / size();
}

int Queue::size() const {

    return queue.size();
}

int Queue::countByStatus(QueueItem::Status status) {
    QLinkedList<QueueItem>::const_iterator it;
    int counter(0);

    for (it = queue.begin(); it != queue.end(); ++it) {
        if (it->getStatus() == status) counter++;
    }

    return counter;
}

int Queue::getUnprocessedCounter() {
    int count = 0;
    foreach (QueueItem item, queue) {
        if (item.getStatus() == QueueItem::WAITING)
            count++;
    }

    return count;
}

QueueItem * Queue::getFirstUnprocessed() {
    QLinkedList<QueueItem>::iterator it;

    for (it = queue.begin(); it != queue.end(); ++it) {
        if (it->getStatus() == QueueItem::WAITING) {
            it->setStatus(QueueItem::PROCESSING);
            return &(*it);
        }
    }

    return NULL;
}

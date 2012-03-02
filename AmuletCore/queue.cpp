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

void Queue::append(const QueueItem & item) {
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

int Queue::size() const {

    return queue.size();
}

int Queue::getProcessedCounter() {

    return processed;
}

int Queue::getUnprocessedCounter() {

    return queue.size() - processed - inProgress;
}

void Queue::addInProgress() {
    inProgress++;
}

QueueItem * Queue::getFirstUnprocessed() {
    QLinkedList<QueueItem>::iterator it;

    for(it = queue.begin() + processed + inProgress; it != queue.end(); ++it) {
        if ((*it).getProgress() == 0) {
            inProgress++;

            return &(*it);
        }
    }

    return NULL;
}

void Queue::update() {
    inProgress--;
    processed++;
}

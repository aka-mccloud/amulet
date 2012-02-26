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

#include "queue_item.hpp"

QueueItem::QueueItem(QFileInfo file, QObject * parent) :
    QObject(parent),
    file(file),
    progress(0) {
}

QueueItem::QueueItem(const QueueItem & item) :
    QObject(item.parent()),
    file(item.file),
    progress(item.progress) {
}

int QueueItem::getProgress() const {

    return progress;
}

const QFileInfo &QueueItem::getFile() const {

    return file;
}

void QueueItem::setPprogress(int progress) {
    this->progress = progress;
}

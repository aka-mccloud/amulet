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

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <QObject>
#include <QLinkedList>

#include "AmuletCore_global.hpp"

#include "queue_item.hpp"

typedef QLinkedList<QueueItem> QueueItemList;

class AMULETCORESHARED_EXPORT Queue : public QObject
{

    Q_OBJECT

private:
    QueueItemList queue;

public:
    explicit Queue(QObject * parent = 0);
    explicit Queue(Queue & queue);
    virtual ~Queue() {}

    void append(QueueItem item);
    QueueItemList::const_iterator begin() const;
    void clear();
    void cleanProgress();
    double countProgress();
    void removeIndices(QList<int> indices);
    int size() const;
    int countByStatus(QueueItem::Status status);
    QueueItem * getFirstUnprocessed();

public slots:

};

#endif // QUEUE_HPP

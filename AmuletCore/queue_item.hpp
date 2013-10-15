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

#ifndef QUEUE_ITEM_HPP
#define QUEUE_ITEM_HPP

#include <QObject>
#include <QFileInfo>

#include "AmuletCore_global.hpp"

class AMULETCORESHARED_EXPORT QueueItem : public QObject
{

    Q_OBJECT

public:
    enum Status
    {
        NONE,
        WAITING,
        PROCESSING,
        STOPPED,
        PROCESSED,
        FAILED
    };

private:
    QFileInfo file;
    int progress;
    Status status;

public:
    explicit QueueItem(QFileInfo file, QObject * parent = 0);
    QueueItem(const QueueItem & item);
    virtual ~QueueItem() {}

    const int getProgress() const;
    const QFileInfo & getFile() const;
    const Status getStatus() const;
    void setStatus(Status status);

public slots:
    void setProgress(int);

};

#endif // QUEUE_ITEM_HPP

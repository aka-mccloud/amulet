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


#ifndef QUEUE_MODEL_H
#define QUEUE_MODEL_H

#include <QAbstractTableModel>

#include "queue.hpp"

class QueueModel : public QAbstractTableModel {

    Q_OBJECT

public:
    enum {
        ProgressRole = 32
    };

private:
    Queue queue;

public:
    explicit QueueModel(QObject *parent = 0);
    virtual ~QueueModel() {}

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role) const;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void append(const QFileInfoList & files);
    void delIndexes(const QModelIndexList & indexList);
    void clear();
    Queue * getQueue();

public slots:
    void updateProgress();

};

#endif // QUEUE_MODEL_H

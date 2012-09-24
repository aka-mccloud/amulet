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

#include <QFileInfo>
#include <QIcon>
#include <QSet>

#include "queue_model.hpp"

QueueModel::QueueModel(QObject * parent)
    : QAbstractTableModel(parent)
{
    // empty
}

void QueueModel::updateProgress()
{
    emit dataChanged(index(0, 1), index(queue.size(), 1));
}

int QueueModel::rowCount(const QModelIndex &) const
{
    return queue.size();
}

int QueueModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant QueueModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
        switch (section) {
        case 0:
            return tr("Title");
        case 1:
            return tr("Progress");
        }
    }

    return QVariant();
}

QVariant QueueModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QueueItemList::const_iterator it = queue.begin() + index.row();
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return (*it).getFile().fileName();
        }
    }

    if (role = ProgressRole) {
        switch (index.column()) {
        case 1:
            return (*it).getProgress();
        }
    }

    return QVariant();
}

void QueueModel::append(const QFileInfoList & files)
{
    foreach(QFileInfo file, files)
        queue.append(QueueItem(file));

    reset();
}

void QueueModel::delIndexes(const QModelIndexList & indexList)
{
    QSet<int> indices;

    foreach (QModelIndex index, indexList)
        indices.insert(index.row());

    queue.removeIndices(indices.toList());

    reset();
}

void QueueModel::clear()
{
    queue.clear();

    reset();
}

Queue * QueueModel::getQueue()
{
    return &queue;
}

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
#include <QMultiMap>

#include "queue_model.hpp"

QueueModel::QueueModel(QObject * parent) :
        QAbstractTableModel(parent) {
}

void QueueModel::updateProgress() {
    emit dataChanged(index(0, 1), index(queue.size(), 1));
}

int QueueModel::rowCount(const QModelIndex &) const {

    return queue.size();
}

int QueueModel::columnCount(const QModelIndex &) const {

    return 2;
}

QVariant QueueModel::headerData(int, Qt::Orientation, int) const {

    return QVariant();
}

QVariant QueueModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    QLinkedList<QueueItem>::const_iterator it = queue.begin() + index.row();
//    FileList::const_iterator it(fileList.begin() + index.row());
//    QLinkedList<QMap<Phonon::MetaData, QString> >::const_iterator iit(metaDataList.begin() + index.row());
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return (*it).getFile().fileName();
        case 1:
            return (*it).getProgress();
        }
    }

//    if (role == Qt::DecorationRole) {
//        switch (index.column()) {
//        case 0:
//            if (it->second == 2) {
//                return QIcon::fromTheme("dialog-ok");
//            }
//            if (it->second == 1) {
//                return QIcon::fromTheme("view-refresh");
//            }
//            return QIcon();
//        }
//    }

    return QVariant();
}

void QueueModel::append(const QFileInfoList & files) {
    foreach(QFileInfo file, files) {
        queue.append(QueueItem(file));
    }

    reset();
}

//void FilesModel::setFileList(const QLinkedList<QString> & list)
//{
//    foreach(QString file, list) {
//        queue.append(QueueItem(QFileInfo(file)));
//    }

//    reset();
//}

//void FilesModel::setFileState(int index, int state) {
//    (fileList.begin() + index)->second = state;
//}

void QueueModel::delIndexes(const QModelIndexList & indexList) {
    //TODO: add implementation
//    QModelIndexList::const_iterator iit;
//    QList<FileList::iterator> itList;

//    for (iit = indexList.begin(); iit != indexList.end(); ++iit) {
//        itList.push_back(fileList.begin() + iit->row());
//    }

//    for (int i = 0; i < indexList.size(); i++) {
//        fileList.erase(itList[i]);
//    }

    reset();
}

void QueueModel::clear() {
    queue.clear();

    reset();
}

Queue * QueueModel::getQueue() {

    return &queue;
}

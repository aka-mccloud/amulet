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

#include <QApplication>
#include <QPainter>

#include "queue_model.hpp"

#include "drop_table_view.hpp"

DropTableView::DropTableView(QWidget * parent) :
    QTreeView(parent) {
    setItemDelegate(new TrackViewDelegate());
}

void DropTableView::dragEnterEvent(QDragEnterEvent * event) {
    event->acceptProposedAction();
}

void DropTableView::dragMoveEvent(QDragMoveEvent * event) {
    event->acceptProposedAction();
}

void DropTableView::dropEvent(QDropEvent * event) {
    emit filesDropped(event->mimeData());
}

TrackViewDelegate::TrackViewDelegate(QObject * parent) :
    QStyledItemDelegate(parent) {

}

void TrackViewDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    if (index.column() != 1) {
        QStyledItemDelegate::paint(painter, option, index);
    } else {
        QStyleOptionProgressBar progressBar;
        progressBar.palette = option.palette;
        progressBar.state = option.state;
        progressBar.rect = option.rect;
        progressBar.minimum = 0;
        progressBar.maximum = 100;
        progressBar.progress = index.model()->data(index, QueueModel::ProgressRole).toInt();
        progressBar.textAlignment = Qt::AlignCenter;
        progressBar.textVisible = true;
        progressBar.text = QString("%1%").arg(progressBar.progress);

        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBar, painter, NULL);
    }
}

QSize TrackViewDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(20);

    return size;
}

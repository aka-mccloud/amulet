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

int QueueItem::getProgress() {

    return progress;
}

const QFileInfo &QueueItem::getFile() {

    return file;
}

void QueueItem::setPprogress(int progress) {
    this->progress = progress;
}

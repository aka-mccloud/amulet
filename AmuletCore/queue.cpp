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

int Queue::getProcessedCounter() {

    return processed;
}

int Queue::getUnprocessedCounter() {

    return queue.size() - processed - inProgress;
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

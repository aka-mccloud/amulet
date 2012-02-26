#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <QObject>
#include <QLinkedList>

#include "queue_item.hpp"

class Queue : public QObject {

    Q_OBJECT

private:
    QLinkedList<QueueItem> queue;
    int processed;
    int inProgress;

public:
    explicit Queue(QObject * parent = 0);
    explicit Queue(Queue & queue);
    virtual ~Queue() {}

    void append(const QueueItem & item);
    int getProcessedCounter();
    int getUnprocessedCounter();
    QueueItem * getFirstUnprocessed();

public slots:
    void update();

};

#endif // QUEUE_HPP

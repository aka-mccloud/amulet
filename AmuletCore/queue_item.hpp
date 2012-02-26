#ifndef QUEUE_ITEM_HPP
#define QUEUE_ITEM_HPP

#include <QObject>
#include <QFileInfo>

class QueueItem : public QObject {

    Q_OBJECT

private:
    QFileInfo file;
    int progress;

public:
    explicit QueueItem(QFileInfo file, QObject * parent = 0);
    explicit QueueItem(const QueueItem & item);
    virtual ~QueueItem() {}

    int getProgress();
    const QFileInfo & getFile();

public slots:
    void setPprogress(int);

};

#endif // QUEUE_ITEM_HPP

#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <QObject>

#include "iworker.hpp"
#include "converter_worker.hpp"

class WorkerPool : public QObject {

    Q_OBJECT

private:
    QLinkedList<IWorker *> workerList;

private slots:
    void jobFinished(IWorker *);

public:
    explicit WorkerPool(QObject * parent = 0);
    virtual ~WorkerPool();

    void execute(IWorker * worker);
    bool isEmpty();
    int size();
    
signals:
    void workerFinished();
    
public slots:
    
};

#endif // WORKER_POOL_HPP

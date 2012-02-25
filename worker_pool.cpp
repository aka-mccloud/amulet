#include "worker_pool.hpp"

WorkerPool::WorkerPool(QObject * parent) :
    QObject(parent) {
}

WorkerPool::~WorkerPool() {
    workerList.clear();
}

void WorkerPool::execute(IWorker * worker) {
    connect(worker, SIGNAL(finished(IWorker *)), this, SLOT(jobFinished(IWorker *)));
    workerList.append(worker);
    worker->start();
}

bool WorkerPool::isEmpty() {

    return workerList.isEmpty();
}

void WorkerPool::jobFinished(IWorker * worker) {
    if (workerList.removeOne(worker)) {
        emit workerFinished();
    }
}

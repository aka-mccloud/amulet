#include "worker_pool.hpp"

WorkerPool::WorkerPool(QObject * parent) :
    QObject(parent) {
}

WorkerPool::~WorkerPool() {
    workerList.clear();
}

void WorkerPool::execute(IWorker * worker) {
    if (worker != NULL) {
        connect(worker->getObject(), SIGNAL(finished(IWorker *)), this, SLOT(jobFinished(IWorker *)));
        workerList.append(worker);
        worker->start();
    } else {
        emit workerFinished();
    }
}

bool WorkerPool::isEmpty() {

    return workerList.isEmpty();
}

int WorkerPool::size() {

    return workerList.size();
}

void WorkerPool::jobFinished(IWorker * worker) {
    if (workerList.removeOne(worker)) {
        worker->getObject()->deleteLater();
        emit workerFinished();
    }
}

#include "worker_pool.hpp"

WorkerPool::WorkerPool(QObject * parent) :
    QObject(parent) {
}

WorkerPool::~WorkerPool() {
    workerList.clear();
}

void WorkerPool::jobFinished(IWorker * worker) {
    if (workerList.removeOne(worker)) {
        worker->getObject()->deleteLater();
        emit workerFinished();
    }
}

void WorkerPool::updateProgress(int) {
    emit progressChanged();
}

void WorkerPool::execute(IWorker * worker) {
    if (worker != NULL) {
        connect(worker->getObject(),
                SIGNAL(finished(IWorker *)),
                SLOT(jobFinished(IWorker *)));
        connect(worker->getObject(),
                SIGNAL(progress(int)),
                SLOT(updateProgress()));
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

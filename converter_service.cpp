#include <QCoreApplication>

#include "converter_service.hpp"

ConverterService::ConverterService(Queue & queue,
                                   const QDir & outDir,
                                   CodecProperties & props,
                                   int threads,
                                   QObject *parent) :
    QObject(parent),
    properties(props),
    queue(queue),
    outDir(outDir),
    threads(threads),
    factory(outDir, props, parent) {
    connect(&pool, SIGNAL(workerFinished()), this, SLOT(pushNext()));
}

ConverterService::~ConverterService() {
    stop();
//    pool.clear();
}

void ConverterService::start() {
    /*if (pool.size() > 0) {
        WorkerPool::iterator it;
        for (it = pool.begin(); it != pool.end(); ++it) {
            (*it)->start();
        }
    }
    int t = threads - pool.size();*/
    for (int i = 0; i < threads; i++) {
        /*if (!queue.isEmpty()) {
            ConverterWorker * worker = factory.create(queue.first());
            if (worker != NULL) {
                connect(worker, SIGNAL(finished()), this, SLOT(pushNext()));
                pool.append(worker);
                worker->start();
            }
            queue.removeFirst();
        }*/
        pushNext();
    }
}

void ConverterService::stop() {
//    WorkerPool::iterator it;
//    for (it = pool.begin(); it != pool.end(); ++it) {
//        (*it)->stop();
//    }
}

void ConverterService::pushNext() {
    /*if (pool.size()) {
        pool.removeFirst();
    }
    if (!queue.isEmpty()) {
        ConverterWorker * worker = factory.create(queue.first());
        if (worker != NULL) {
            connect(worker, SIGNAL(finished()), this, SLOT(pushNext()));
            pool.append(worker);
            worker->start();
        }
        queue.removeFirst();
    } else if (pool.isEmpty()) {
//        emit finished();
        QCoreApplication::exit(0);
    }*/
    if (!queue.isEmpty()) {
    IWorker * worker = factory.create(queue.first());
    if (worker != NULL) {
        pool.execute(worker);
    }
    queue.removeFirst();
    } else if (pool.isEmpty()) {
//        emit finished();
        QCoreApplication::exit(0);
    }

}

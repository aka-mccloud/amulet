#include <QCoreApplication>

#include "converter_service.hpp"

ConverterService::ConverterService(Queue & queue,
                                   const QDir & outDir,
                                   const CodecProperties & props,
                                   int threads,
                                   QObject *parent) :
    QObject(parent),
    properties(props),
    queue(queue),
    outDir(outDir),
    work(true),
    threads(threads),
    factory(outDir, props, parent) {
}

ConverterService::~ConverterService() {
    stop();
    pool.clear();
}

void ConverterService::start() {
    if (pool.size() > 0) {
        WorkerPool::iterator it;
        for (it = pool.begin(); it != pool.end(); ++it) {
            (*it)->start();
        }
    }
    int t = threads - pool.size();
    for (int i = 0; i < t; i++) {
        if (!queue.isEmpty()) {
            ConverterWorker * worker = factory.create(queue.first());
            connect(worker, SIGNAL(finished()), this, SLOT(pushNext()));
            pool.append(worker);
            queue.removeFirst();
            worker->start();
        }
    }
}

void ConverterService::stop() {
    WorkerPool::iterator it;
    for (it = pool.begin(); it != pool.end(); ++it) {
        (*it)->stop();
    }
}

void ConverterService::pushNext() {
    pool.removeFirst();
    if (!queue.isEmpty()) {
        ConverterWorker * worker = factory.create(queue.first());
        connect(worker, SIGNAL(finished()), this, SLOT(pushNext()));
        pool.append(worker);
        queue.removeFirst();
        worker->start();
    } else if (pool.isEmpty()) {
//        emit finished();
        QCoreApplication::exit(0);
    }
}

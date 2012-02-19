#include <QCoreApplication>

#include "converter_service.hpp"

ConverterService::ConverterService(Queue & queue,
                                   const QDir & outDir,
                                   const CodecProperties & props,
                                   QObject * parent) :
    QObject(parent),
    properties(props),
    queue(queue),
    outDir(outDir),
    work(true),
    threads(3),
    factory(outDir, props, parent) {
}

void ConverterService::start() {
    if (pool.size() > 0) {
        WorkerPool::iterator it;
        for (it = pool.begin(); it != pool.end(); ++it) {
            (*it)->start();
        }
    }
    for (int i = 0; i < threads - pool.size(); ++i) {
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
        //emit finished();
        QCoreApplication::exit(0);
    }
}

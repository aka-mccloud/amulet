#include <QCoreApplication>

#include "converter_service.hpp"

ConverterService::ConverterService(Queue & queue,
                                   const QDir & outDir,
                                   CodecProperties & props,
                                   int threads,
                                   QObject * parent) :
    QObject(parent),
    properties(props),
    queue(queue),
    outDir(outDir),
    threads(threads),
    factory(outDir, props, parent),
    pool(parent) {
    connect(&pool, SIGNAL(workerFinished()), this, SLOT(pushNext()));
}

ConverterService::~ConverterService() {
    stop();
}

void ConverterService::start() {
    for (int i = 0; i < threads; i++) {
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
    if (!queue.isEmpty()) {
        IWorker * worker = factory.create(queue.first());
        queue.removeFirst();
        pool.execute(worker);
    } else if (pool.isEmpty()) {
        //        emit finished();
        exit(0);
    }

}

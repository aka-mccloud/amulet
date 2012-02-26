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
    connect(&pool,
            SIGNAL(workerFinished()),
            SLOT(pushNext()));
    connect(&pool,
            SIGNAL(progressChanged()),
            SLOT(updateProgress()));
}

ConverterService::~ConverterService() {
    stop();
}

void ConverterService::pushNext() {
    if (queue.getUnprocessedCounter() != 0) {
        IWorker * worker = factory.create(queue.getFirstUnprocessed());
        pool.execute(worker);
    } else if (pool.isEmpty()) {
//        emit finished();
        exit(0);
    }

}

void ConverterService::updateProgress() {
    emit progressChanged();
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

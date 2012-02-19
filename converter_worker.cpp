#include <QDebug>

#include "converter_worker.hpp"

ConverterWorker::ConverterWorker(Decoder *decoder,
                                 Coder *coder,
                                 QObject * parent) :
    QObject(parent),
    decoder(decoder),
    coder(coder),
    completed(0) {
    this->decoder->getProcessInstance()->setStandardOutputProcess(
                this->coder->getProcessInstance());
    connect(this->coder, SIGNAL(finished()), this, SLOT(endConvert()));
    connect(this->decoder, SIGNAL(progress(int)), this, SLOT(progressReady(int)));
}

ConverterWorker::~ConverterWorker() {
    delete decoder;
    delete coder;
}

void ConverterWorker::start() {
    decoder->start();
    coder->start();
}

void ConverterWorker::stop() {
    decoder->stop();
    coder->stop();
}

void ConverterWorker::endConvert() {
    emit finished();
}

void ConverterWorker::progressReady(int p) {
    qDebug() << p;
    emit progress(p);
}

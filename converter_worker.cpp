#include <QDebug>

#include "converter_worker.hpp"

ConverterWorker::ConverterWorker(Decoder *decoder,
                                 Encoder *coder,
                                 QObject * parent) :
    IWorker(parent),
    decoder(decoder),
    encoder(coder),
    completed(0) {
    this->decoder->getProcessInstance()->setStandardOutputProcess(
                this->encoder->getProcessInstance());
    connect(this->encoder, SIGNAL(finished()), this, SLOT(endConvert()));
    connect(this->decoder, SIGNAL(progress(int)), this, SLOT(progressReady(int)));
}

ConverterWorker::~ConverterWorker() {
    stop();
    delete decoder;
    delete encoder;
}

void ConverterWorker::start() {
    decoder->start();
    encoder->start();
}

void ConverterWorker::stop() {
    decoder->stop();
    encoder->stop();
}

void ConverterWorker::endConvert() {

    emit finished(this);
}

void ConverterWorker::progressReady(int p) {
    qDebug() << p;
    emit progress(p);
}

#include <QDebug>

#include "converter_worker.hpp"

ConverterWorker::ConverterWorker(IDecoderProcess * decoder,
                                 IEncoderProcess * encoder,
                                 QObject * parent) :
    QObject(parent),
    decoder(decoder),
    encoder(encoder),
    completed(0) {
    this->decoder->getProcessInstance()->setStandardOutputProcess(this->encoder->getProcessInstance());
    connect(this->encoder->getObject(), SIGNAL(finished()),
            SLOT(endConvert()));
    connect(this->decoder->getObject(), SIGNAL(progress(int)),
            SLOT(progressReady(int)));
}

ConverterWorker::~ConverterWorker() {
    stop();
    delete decoder;
    delete encoder;
}

QObject * ConverterWorker::getObject() {

    return this;
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

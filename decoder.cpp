#include "decoder.hpp"

Decoder::Decoder(const QString & fileName,
                 QObject *parent) :
    QObject(parent) {
    args += QString("-d");
    args += QString("-c");
    args += fileName;

    process = new QProcess(parent);
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(calculateProgress()));
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

Decoder::~Decoder() {
    delete process;
}

QProcess * Decoder::getProcessInstance() {

    return process;
}

void Decoder::start() {
    process->start(decoderName, args);
}

void Decoder::stop() {
    process->terminate();
}

void Decoder::calculateProgress() {
    QString out(process->readAllStandardError());
    QRegExp rx("([\\d]{1,3})% complete");

    if (rx.indexIn(out) >= 0) {
        //qDebug() << rx.cap(1);
        completed = rx.cap(1).toInt();

        emit progress(completed);
    }
}

void Decoder::finished(int) {
    emit finished();
}

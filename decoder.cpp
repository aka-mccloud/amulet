#include "decoder.hpp"

Decoder::Decoder(QObject * parent) :
    QObject(parent) {
    args += QString("-d");

    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(calculateProgress()));
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

Decoder::~Decoder() {
    delete process;
}

void Decoder::setInputFile(const QString & fileName) {
    inputFile = fileName;
}

void Decoder::setOutputFile(const QString & fileName) {
    outputFile = fileName;
}

QProcess * Decoder::getProcessInstance() {

    return process;
}

QObject * Decoder::getObject() {

    return this;
}

void Decoder::start() {
    args += inputFile;
    if (outputFile.isEmpty()) {
        args += QString("-c");
    } else {
        args += outputFile;
    }

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

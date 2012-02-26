#include "encoder.hpp"

Encoder::Encoder(QObject * parent) :
    QObject(parent) {

    process = new QProcess(this);
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

Encoder::~Encoder() {
    delete process;
}

void Encoder::setOutputFile(const QString & fileName) {
    outputFile = fileName;
}

void Encoder::setProperties(const CodecProperties & props) {
    args += props.toStringList();
}

QProcess * Encoder::getProcessInstance() {

    return process;
}

QObject * Encoder::getObject() {

    return this;
}

void Encoder::start() {
    if (inputFile.isEmpty()) {
        args += QString("-");
    } else {
        args += inputFile;
    }
    args += outputFile;

    process->start(coderName, args);
}

void Encoder::stop() {
    process->terminate();
}

void Encoder::finished(int) {
    emit finished();
}

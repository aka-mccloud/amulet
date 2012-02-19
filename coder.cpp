#include "coder.hpp"

Coder::Coder(CodecProperties & props,
             const QString & fileName,
             QObject * parent) :
    QObject(parent) {
    args += props.toStringList();
    args += QString("-");
    args += fileName;

    process = new QProcess(parent);
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

Coder::~Coder() {
    delete process;
}

QProcess * Coder::getProcessInstance() {

    return process;
}

void Coder::start() {
    process->start(coderName, args);
}

void Coder::stop() {
    process->terminate();
}

void Coder::finished(int) {
    emit finished();
}

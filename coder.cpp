#include "coder.hpp"

Coder::Coder(QObject * parent) :
    QObject(parent) {
    process = new QProcess(parent);
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

Coder::~Coder() {
    delete process;
}

void Coder::setOutputFile(const QString & fileName) {
    outputFile = fileName;
}

void Coder::setProperties(CodecProperties & props) {
    args += props.toStringList();
}

QProcess * Coder::getProcessInstance() {

    return process;
}

void Coder::start() {
    if (inputFile.isEmpty()) {
        args += QString("-");
    } else {
        args += inputFile;
    }
    args += outputFile;

    process->start(coderName, args);
}

void Coder::stop() {
    process->terminate();
}

void Coder::finished(int) {
    emit finished();
}

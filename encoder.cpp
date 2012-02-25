#include "encoder.hpp"

Encoder::Encoder(CodecProperties & props,
             QObject * parent) :
    QObject(parent) {
    args += props.toStringList();

    process = new QProcess(parent);
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

Encoder::~Encoder() {
    delete process;
}

void Encoder::setOutputFile(const QString & fileName) {
    outputFile = fileName;
}

//void Coder::setProperties(CodecProperties & props) {
//    args += props.toStringList();
//}

QProcess * Encoder::getProcessInstance() {

    return process;
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

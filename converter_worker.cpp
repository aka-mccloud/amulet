#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "converter_worker.hpp"

ConverterWorker::ConverterWorker(const QFileInfo & inFile,
                                 const QDir & outDir,
                                 const CodecProperties &props,
                                 QObject * parent) :
    QObject(parent),
    properties(props),
    inFile(inFile),
    outDir(outDir),
    completed(0) {
    coder = new QProcess();
    decoder = new QProcess();
    connect(coder, SIGNAL(finished(int)), this, SLOT(endConvert(int)));
    connect(decoder, SIGNAL(readyReadStandardError()), this, SLOT(calculateProgress()));
}

ConverterWorker::~ConverterWorker() {
    delete decoder;
    delete coder;
}

void ConverterWorker::run() {
    QString outFile = outDir.absolutePath() + "/" +
            inFile.completeBaseName() + "." + extension;
    QStringList decoderArguments;
    decoderArguments += QString("-d");
    decoderArguments += QString("-c");
    decoderArguments += inFile.absoluteFilePath();

    QStringList coderArguments;
    coderArguments += properties.toStringList();
    coderArguments += QString("-");
    coderArguments += outFile;

    decoder->setStandardOutputProcess(coder);
    decoder->start(decoderName, decoderArguments);
    coder->start(coderName, coderArguments);
}

void ConverterWorker::endConvert(int) {
    QCoreApplication::exit(0);
}

void ConverterWorker::calculateProgress() {
    QString output(decoder->readAllStandardError());
    QRegExp rx("([\\d]{1,3})% complete");

    if (rx.indexIn(output) >= 0) {
        qDebug() << rx.cap(1);
        completed = rx.cap(1).toInt();

        emit progress(completed);
    }
}

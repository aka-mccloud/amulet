#include "converter_factory.hpp"

ConverterFactory::ConverterFactory(const QDir &outDir,
                                   const CodecProperties &props,
                                   QObject * parent) :
    QObject(parent),
    properties(props),
    outDir(outDir) {
}

ConverterWorker * ConverterFactory::create(const QFileInfo inFile) {

    return new ConverterWorker(inFile, outDir, properties);
}

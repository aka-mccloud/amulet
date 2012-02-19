#include "coder.hpp"
#include "decoder.hpp"
#include "converter_factory.hpp"

ConverterFactory::ConverterFactory(const QDir &outDir,
                                   const CodecProperties &props,
                                   QObject * parent) :
    QObject(parent),
    properties(props),
    outDir(outDir) {
}

ConverterWorker * ConverterFactory::create(const QFileInfo inFile) {
    QString outFile = outDir.absolutePath() + "/" +
                inFile.completeBaseName() + "." + extension;

    return new ConverterWorker(new Decoder(inFile.absoluteFilePath()),
                               new Coder(properties, outFile),
                               this);
}

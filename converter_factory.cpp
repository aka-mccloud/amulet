#include "coder.hpp"
#include "codec_flac.hpp"
#include "codec_lame.hpp"
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
    Decoder * decoder = CodecFlac::getDecoder();
    decoder->setInputFile(inFile.absoluteFilePath());
    Coder * coder = CodecLame::getCodec();
    coder->setProperties(properties);
    coder->setOutputFile(outFile);

    return new ConverterWorker(decoder, coder, this);
}

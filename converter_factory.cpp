#include "converter_factory.hpp"

ConverterFactory::ConverterFactory(const QDir & outDir,
                                   CodecProperties & props,
                                   QObject * parent) :
    QObject(parent),
    outDir(outDir),
    codecFactory(props) {
}

ConverterWorker * ConverterFactory::create(const QFileInfo inFile) {
    ConverterWorker * converterWorker = NULL;
    Decoder * decoder = codecFactory.getDecoderForType(inFile.suffix());
    Encoder * coder = codecFactory.getEncoderForType(extension);

    if ((decoder != NULL) && (coder != NULL)) {
        QString outFile = outDir.absolutePath() + "/" +
                    inFile.completeBaseName() + "." + extension;
        decoder->setInputFile(inFile.absoluteFilePath());
        coder->setOutputFile(outFile);

        converterWorker = new ConverterWorker(decoder, coder, this);
    }

    return converterWorker;
}

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
    IDecoderProcess * decoder = codecFactory.getDecoderForType(inFile.suffix());
    IEncoderProcess * encoder = codecFactory.getEncoderForType("mp3");

    if ((decoder != NULL) && (encoder != NULL)) {
        QString outFile = outDir.absolutePath() + "/" +
                    inFile.completeBaseName() + ".mp3";
        decoder->setInputFile(inFile.absoluteFilePath());
        encoder->setOutputFile(outFile);

        converterWorker = new ConverterWorker(decoder, encoder, this);
    }

    return converterWorker;
}

#include <QFileInfo>

#include "converter_factory.hpp"

ConverterFactory::ConverterFactory(const QDir & outDir,
                                   CodecProperties & props,
                                   QObject * parent) :
    QObject(parent),
    outDir(outDir),
    properties(props) {
}

ConverterWorker * ConverterFactory::create(QueueItem * item) {
    ConverterWorker * converterWorker = NULL;

    if (item != NULL) {
        QFileInfo file = item->getFile();
        IDecoderProcess * decoder = codecFactory.getDecoderForType(file.suffix());
        IEncoderProcess * encoder = codecFactory.getEncoderForType("mp3");

        if ((decoder != NULL) && (encoder != NULL)) {
            QString outFile = outDir.absolutePath() + "/" +
                    file.completeBaseName() + ".mp3";
            decoder->setInputFile(file.absoluteFilePath());
            encoder->setOutputFile(outFile);
            encoder->setProperties(properties);

            converterWorker = new ConverterWorker(decoder, encoder, this);
            connect(converterWorker,
                    SIGNAL(progress(int)),
                    item,
                    SLOT(setPprogress(int)));
        }
    }

    return converterWorker;
}

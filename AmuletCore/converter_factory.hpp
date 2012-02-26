#ifndef CONVERTER_FACTORY_HPP
#define CONVERTER_FACTORY_HPP

#include <QObject>
#include <QDir>

#include "codec_factory.hpp"
#include "converter_worker.hpp"
#include "queue_item.hpp"

class ConverterFactory : public QObject {

    Q_OBJECT

private:
    QDir outDir;
    CodecProperties properties;
    CodecFactory codecFactory;

public:
    explicit ConverterFactory(const QDir & outDir,
                              CodecProperties & props,
                              QObject * parent = 0);
    virtual ~ConverterFactory() {}

    ConverterWorker * create(QueueItem * item);

};

#endif // CONVERTER_FACTORY_HPP

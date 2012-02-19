#ifndef CONVERTER_FACTORY_HPP
#define CONVERTER_FACTORY_HPP

#include <QObject>
#include <QFileInfo>
#include <QDir>

#include "codec_properties.hpp"
#include "converter_worker.hpp"

class ConverterFactory : public QObject {

    Q_OBJECT

private:
    CodecProperties properties;
    QDir outDir;

public:
    explicit ConverterFactory(const QDir & outDir,
                              const CodecProperties & props,
                              QObject * parent = 0);

    ConverterWorker * create(const QFileInfo inFile);
    
signals:
    
public slots:
    
};

#endif // CONVERTER_FACTORY_HPP

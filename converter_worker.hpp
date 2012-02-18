#ifndef CONVERTER_WORKER_HPP
#define CONVERTER_WORKER_HPP

#include <QThread>
#include <QProcess>
#include <QFileInfo>
#include <QDir>

#include "codec_properties.hpp"

#define extension "mp3"
#define coderName "lame"
#define decoderName "flac"

class ConverterWorker : public QObject {

    Q_OBJECT

private:
    CodecProperties properties;
    QFileInfo inFile;
    QDir outDir;
    QProcess * decoder;
    QProcess * coder;
    int completed;

private slots:
    void endConvert(int);
    void calculateProgress();

protected:


public:
    ConverterWorker(const QFileInfo & inFile,
                    const QDir & outDir,
                    const CodecProperties & props,
                    QObject * parent = 0);
    virtual ~ConverterWorker();

    void run();

signals:
    void progress(int);

};

#endif // CONVERTER_WORKER_HPP

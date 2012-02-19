#ifndef CONVERTER_WORKER_HPP
#define CONVERTER_WORKER_HPP

#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QLinkedList>

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

signals:
    void progress(int);
    void finished();

public slots:
    void start();
    void stop();
};

typedef QLinkedList<ConverterWorker *> WorkerPool;

#endif // CONVERTER_WORKER_HPP

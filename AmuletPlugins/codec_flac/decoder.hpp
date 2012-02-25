#ifndef DECODER_HPP
#define DECODER_HPP

#include <QObject>
#include <QProcess>
#include <QStringList>

#include "idecoder_process.hpp"

#define decoderName "flac"

class Decoder : public QObject, public IDecoderProcess {

    Q_OBJECT
    Q_INTERFACES(IDecoderProcess)

private:
    QProcess * process;
    QStringList args;
    QString inputFile;
    QString outputFile;
    int completed;

private slots:
    void calculateProgress();
    void finished(int);

public:
    explicit Decoder(QObject * parent = 0);
    virtual ~Decoder();

    void setInputFile(const QString & fileName);
    void setOutputFile(const QString & fileName);
    QProcess * getProcessInstance();
    QObject * getObject();

signals:
    void progress(int);
    void finished();

public slots:
    void start();
    void stop();

};

#endif // DECODER_HPP

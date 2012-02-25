#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <QObject>
#include <QProcess>
#include <QStringList>

#include "codec_properties.hpp"
#include "iencoder_process.hpp"

#define coderName "lame"
#define extension "mp3"

class Encoder : public QObject, public IEncoderProcess {

    Q_OBJECT
    Q_INTERFACES(IEncoderProcess)

private:
    QProcess * process;
    QStringList args;
    QString inputFile;
    QString outputFile;

private slots:
    void finished(int);

public:
    explicit Encoder(QObject * parent = 0);
    virtual ~Encoder();

    void setProperties(const CodecProperties & props);
    void setOutputFile(const QString & fileName);
    QProcess * getProcessInstance();
    QObject * getObject();

signals:
    void finished();

public slots:
    void start();
    void stop();

};

#endif // ENCODER_HPP

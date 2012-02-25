#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <QObject>
#include <QProcess>
#include <QStringList>

#include "codec_properties.hpp"

#define coderName "lame"
#define extension "mp3"

class Encoder : public QObject {

    Q_OBJECT

private:
    QProcess * process;
    QStringList args;
    QString inputFile;
    QString outputFile;

private slots:
    void finished(int);

public:
    explicit Encoder(CodecProperties & props,
                   QObject * parent = 0);
    virtual ~Encoder();

    void setOutputFile(const QString & fileName);
//    void setProperties(CodecProperties & props);
    QProcess * getProcessInstance();

signals:
    void finished();

public slots:
    void start();
    void stop();

};

#endif // ENCODER_HPP

#ifndef CODER_HPP
#define CODER_HPP

#include <QObject>
#include <QProcess>
#include <QStringList>

#include "codec_properties.hpp"

#define coderName "lame"
#define extension "mp3"

class Coder : public QObject
{
    Q_OBJECT

private:
    QProcess * process;
    QStringList args;

private slots:
    void finished(int);

public:
    explicit Coder(CodecProperties & props,
                   const QString & fileName,
                   QObject * parent = 0);
    virtual ~Coder();
    QProcess * getProcessInstance();

signals:
    void finished();

public slots:
    void start();
    void stop();

};

#endif // CODER_HPP

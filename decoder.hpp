#ifndef DECODER_HPP
#define DECODER_HPP

#include <QObject>
#include <QProcess>
#include <QStringList>

#define decoderName "flac"

class Decoder : public QObject
{
    Q_OBJECT

private:
    QProcess * process;
    QStringList args;
    int completed;

private slots:
    void calculateProgress();
    void finished(int);

public:
    explicit Decoder(const QString & fileName,
                     QObject * parent = 0);
    virtual ~Decoder();
    QProcess * getProcessInstance();

signals:
    void progress(int);
    void finished();

public slots:
    void start();
    void stop();

};

#endif // DECODER_HPP

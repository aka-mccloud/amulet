#ifndef CONVERTER_WORKER_HPP
#define CONVERTER_WORKER_HPP

#include <QLinkedList>

#include "iworker.hpp"
#include "idecoder_process.hpp"
#include "iencoder_process.hpp"

class ConverterWorker : public QObject, public IWorker {

    Q_OBJECT
    Q_INTERFACES(IWorker)

private:
    IDecoderProcess * decoder;
    IEncoderProcess * encoder;
    int completed;

private slots:
    void endConvert();
    void progressReady(int p);

public:
    explicit ConverterWorker(IDecoderProcess * decoder,
                             IEncoderProcess * encoder,
                             QObject * parent = 0);
    virtual ~ConverterWorker();

    QObject * getObject();

public slots:
    void start();
    void stop();

signals:
    void progress(int);
    void finished(IWorker *);

};

#endif // CONVERTER_WORKER_HPP

#ifndef CONVERTER_WORKER_HPP
#define CONVERTER_WORKER_HPP

#include <QLinkedList>

#include "iworker.hpp"
#include "encoder.hpp"
#include "decoder.hpp"

class ConverterWorker : public IWorker {

    Q_OBJECT

private:
    Decoder * decoder;
    Encoder * encoder;
    int completed;

private slots:
    void endConvert();
    void progressReady(int p);

public:
    explicit ConverterWorker(Decoder * decoder,
                             Encoder * encoder,
                             QObject * parent = 0);
    virtual ~ConverterWorker();

//signals:
//    void progress(int);
//    void finished();

public:
    void start();
    void stop();
};

#endif // CONVERTER_WORKER_HPP

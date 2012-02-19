#ifndef CONVERTER_WORKER_HPP
#define CONVERTER_WORKER_HPP

#include <QLinkedList>

#include "coder.hpp"
#include "decoder.hpp"

class ConverterWorker : public QObject {

    Q_OBJECT

private:
    Decoder * decoder;
    Coder * coder;
    int completed;

private slots:
    void endConvert();
    void progressReady(int p);

protected:

public:
    explicit ConverterWorker(Decoder * decoder,
                             Coder * coder,
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

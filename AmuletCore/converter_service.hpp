#ifndef CONVERTER_SERVICE_HPP
#define CONVERTER_SERVICE_HPP

#include <QObject>
#include <QFileInfo>
#include <QList>
#include <QDir>

#include "codec_properties.hpp"
#include "converter_factory.hpp"
#include "worker_pool.hpp"

#include "AmuletCore_global.hpp"

typedef QList<QFileInfo> Queue;

class AMULETCORESHARED_EXPORT ConverterService : public QObject {

    Q_OBJECT

private:
    CodecProperties properties;
    Queue queue;
    QDir outDir;
    int threads;
    ConverterFactory factory;
    WorkerPool pool;

private slots:
    void pushNext();

public:
    explicit ConverterService(Queue & queue,
                              const QDir & outDir,
                              CodecProperties & props,
                              int threads,
                              QObject * parent = 0);
    virtual ~ConverterService();
    
signals:
    void finished();
    
public slots:
    void start();
    void stop();

};

#endif // CONVERTER_SERVICE_HPP

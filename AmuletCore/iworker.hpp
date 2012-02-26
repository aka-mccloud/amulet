#ifndef IWORKER_HPP
#define IWORKER_HPP

#include <QObject>

class IWorker {

public:
    virtual ~IWorker() {}

    virtual QObject * getObject() = 0;

//public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

//signals:
    virtual void progress(int) = 0;
    virtual void finished(IWorker *) = 0;

};

Q_DECLARE_INTERFACE(IWorker, "org.amulet.IWorker")

#endif // IWORKER_HPP

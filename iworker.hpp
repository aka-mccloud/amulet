#ifndef IWORKER_HPP
#define IWORKER_HPP

#include <QObject>

class IWorker/* : public QObject */{

//    Q_OBJECT

//signals:
//    void progress(int);
//    void finished(IWorker *);

public:
//    explicit IWorker(QObject * parent = 0) :
//        QObject(parent) {

//    }
    virtual ~IWorker() {}

    virtual QObject * getObject() = 0;

//public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

};

Q_DECLARE_INTERFACE(IWorker, "org.amulet.IWorker")

#endif // IWORKER_HPP

#ifndef IWORKER_HPP
#define IWORKER_HPP

#include <QObject>

class IWorker : public QObject {

    Q_OBJECT

public:
    explicit IWorker(QObject * parent = 0) :
        QObject(parent) {

    }

signals:
    void progress(int);
    void finished(IWorker *);

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

};

#endif // IWORKER_HPP

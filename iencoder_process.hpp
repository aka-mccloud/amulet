#ifndef IENCODER_PROCESS_HPP
#define IENCODER_PROCESS_HPP

#include <QObject>
#include <QString>
#include <QProcess>

class IEncoderProcess/* : public QObject */{

//    Q_OBJECT

//signals:
    virtual void finished() = 0;

public:
    virtual ~IEncoderProcess() {}

    virtual void setOutputFile(const QString & fileName) = 0;
    virtual QProcess * getProcessInstance() = 0;
    virtual QObject * getObject() = 0;

//public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

};

Q_DECLARE_INTERFACE(IEncoderProcess, "org.amulet.IEncoderProcess")

#endif // IENCODER_PROCESS_HPP

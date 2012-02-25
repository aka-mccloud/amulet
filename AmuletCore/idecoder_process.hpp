#ifndef IDECODER_PROCESS_H
#define IDECODER_PROCESS_H

#include <QObject>
#include <QString>
#include <QProcess>

class IDecoderProcess {

//signals:
    virtual void progress(int) = 0;
    virtual void finished() = 0;

public:
    virtual ~IDecoderProcess() {}

    virtual void setInputFile(const QString & fileName) = 0;
    virtual QProcess * getProcessInstance() = 0;
    virtual QObject * getObject() = 0;

//public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

};

Q_DECLARE_INTERFACE(IDecoderProcess, "org.amulet.IDecoderProcess")

#endif // IDECODER_PROCESS_H

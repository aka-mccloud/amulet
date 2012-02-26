#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

#include "converter_service.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Queue queue;
    queue.append(QueueItem(QFileInfo("02 - Injection.flac")));
    queue.append(QueueItem(QFileInfo("03 - Ready to Fall.flac")));
    queue.append(QueueItem(QFileInfo("09 - Give It All.flac")));
    queue.append(QueueItem(QFileInfo("12 - The Good Left Undone.flac")));
    QDir outDir(QCoreApplication::applicationDirPath());

    CodecProperties properties;
    properties[CodecProperties::BITRATE] = "320";
    properties[CodecProperties::SAMPLERATE] = "44.1";
    properties[CodecProperties::LOWPASS] = "22";

    ConverterService service(queue, outDir, properties, 3, &a);
    //QObject::connect(&service, SIGNAL(finished()), &a, SLOT(quit()));
    service.start();

    return a.exec();
}

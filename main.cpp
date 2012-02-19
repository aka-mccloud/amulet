#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

#include "converter_service.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

//    QFileInfo inFile("09 - Give It All.flac");
    Queue queue;
    queue.append(QFileInfo("02 - Injection.flac"));
    queue.append(QFileInfo("03 - Ready to Fall.flac"));
    queue.append(QFileInfo("09 - Give It All.flac"));
    queue.append(QFileInfo("12 - The Good Left Undone.flac"));
    QDir outDir(queue.first().absoluteDir());

    CodecProperties properties;
    properties[CodecProperties::BITRATE] = "320";
    properties[CodecProperties::SAMPLERATE] = "44.1";
    properties[CodecProperties::LOWPASS] = "22";

    ConverterService service(queue, outDir, properties, 3, &a);
    QObject::connect(&service, SIGNAL(finished()), &a, SLOT(quit()));
    service.start();

    return a.exec();
}

#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

#include "converter_service.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QFileInfo inFile("09 - Give It All.flac");
    Queue queue;
    queue.append(inFile);
    QDir outDir(inFile.absoluteDir());

    CodecProperties properties;
    properties[CodecProperties::BITRATE] = "320";
    properties[CodecProperties::SAMPLERATE] = "44.1";
    properties[CodecProperties::LOWPASS] = "22";

//    ConverterWorker converter(inFile, outDir, properties, &a);
//    converter.run();

    ConverterService service(queue, outDir, properties, &a);
    QObject::connect(&service, SIGNAL(finished()), &a, SLOT(quit()));
    service.start();

    return a.exec();
}

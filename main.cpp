#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

#include <converter_worker.hpp>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QFileInfo inFile("09 - Give It All.flac");
    QDir outDir(inFile.absoluteDir());

    CodecProperties properties;
    properties[CodecProperties::BITRATE] = "320";
    properties[CodecProperties::SAMPLERATE] = "44.1";
    properties[CodecProperties::LOWPASS] = "22";

    ConverterWorker converter(inFile, outDir, properties, &a);
    converter.run();

    return a.exec();
}

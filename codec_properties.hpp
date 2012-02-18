#ifndef CODEC_PROPERTIES_HPP
#define CODEC_PROPERTIES_HPP

#include <QString>
#include <QStringList>
#include <QMap>

class CodecProperties {

public:
    enum Options {
        BITRATE,
        SAMPLERATE,
        LOWPASS
    };

private:
    QMap<Options, QString> values;
    QMap<Options, QString> options;

public:
    CodecProperties();

    QString toString();
    QStringList toStringList();

    QString & operator [] (Options option) {
        return values[option];
    }

};

#endif // CODEC_PROPERTIES_HPP

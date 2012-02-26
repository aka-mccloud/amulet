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
    explicit CodecProperties();
    virtual ~CodecProperties() {}

//    QString toString();
    QStringList toStringList() const;

    QString & operator [](Options option);

};

#endif // CODEC_PROPERTIES_HPP

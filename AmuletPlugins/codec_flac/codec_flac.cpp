#include <QtPlugin>

#include "codec_provider.hpp"
#include "codec_flac.hpp"

CodecFlac::CodecFlac() {
    codecProvider = new CodecProvider();
    formats += "flac";
}

QStringList CodecFlac::getFromats() {

    return formats;
}

ICodecProvider * CodecFlac::getCodec() {

    return codecProvider;
}

QWidget * CodecFlac::getWidget() {

    return NULL;
}

Q_EXPORT_PLUGIN(CodecFlac)

#include <QtPlugin>

#include "codec_provider.hpp"
#include "codec_lame.hpp"

CodecLame::CodecLame() {
    codecProvider = new CodecProvider();
    formats += "mp3";
}

QStringList CodecLame::getFromats() {

    return formats;
}

ICodecProvider *CodecLame::getCodec() {

    return codecProvider;
}

QWidget *CodecLame::getWidget() {

    return NULL;
}

Q_EXPORT_PLUGIN(CodecLame)

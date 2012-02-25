#include "codec_factory.hpp"

CodecFactory::CodecFactory(CodecProperties & props) {
    codecMap["flac"] = new CodecFlac(props);
    codecMap["mp3"] = new CodecLame(props);
}

CodecFactory::~CodecFactory() {

}

Decoder * CodecFactory::getDecoderForType(const QString & type) {
    Decoder * decoder = NULL;
    if (codecMap.contains(type)) {
        decoder = codecMap[type]->getDecoder();
    }

    return decoder;
}

Encoder * CodecFactory::getEncoderForType(const QString & type) {
    Encoder * coder = NULL;
    if (codecMap.contains(type)) {
        coder = codecMap[type]->getEncoder();
    }

    return coder;
}

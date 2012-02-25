#include "codec_factory.hpp"

CodecFactory::CodecFactory(CodecProperties & props) {
    codecMap["flac"] = new CodecFlac(props);
    codecMap["mp3"] = new CodecLame(props);
}

CodecFactory::~CodecFactory() {

}

IDecoderProcess * CodecFactory::getDecoderForType(const QString & type) {
    IDecoderProcess * decoder = NULL;
    if (codecMap.contains(type)) {
        decoder = codecMap[type]->getDecoder();
    }

    return decoder;
}

IEncoderProcess * CodecFactory::getEncoderForType(const QString & type) {
    IEncoderProcess * coder = NULL;
    if (codecMap.contains(type)) {
        coder = codecMap[type]->getEncoder();
    }

    return coder;
}

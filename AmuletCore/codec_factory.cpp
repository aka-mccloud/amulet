#include "codec_factory.hpp"

CodecFactory::CodecFactory() {
    codecMap = plugins.getCodecMap();
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

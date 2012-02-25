#include "encoder.hpp"
#include "codec_provider.hpp"

CodecProvider::CodecProvider() {
}

IDecoderProcess * CodecProvider::getDecoder() {

    return NULL;
}

IEncoderProcess * CodecProvider::getEncoder() {

    return new Encoder();
}

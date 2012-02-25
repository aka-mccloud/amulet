#include "decoder.hpp"
#include "codec_provider.hpp"

CodecProvider::CodecProvider() {
}

IDecoderProcess * CodecProvider::getDecoder() {

    return new Decoder();
}

IEncoderProcess * CodecProvider::getEncoder() {

    return NULL;
}

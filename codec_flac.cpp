#include "decoder.hpp"
#include "codec_flac.hpp"

CodecFlac::CodecFlac(CodecProperties & props) :
    properties(props) {
}

IDecoderProcess * CodecFlac::getDecoder() {

    return new Decoder();
}

IEncoderProcess * CodecFlac::getEncoder() {

    return NULL;
}

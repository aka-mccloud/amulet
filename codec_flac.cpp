#include "codec_flac.hpp"

CodecFlac::CodecFlac(CodecProperties & props) :
    properties(props) {
}

Decoder * CodecFlac::getDecoder() {

    return new Decoder();
}

Encoder *CodecFlac::getEncoder() {

    return NULL;
}

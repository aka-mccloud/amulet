#include "codec_flac.hpp"

CodecFlac::CodecFlac() {
}

Decoder * CodecFlac::getDecoder() {

    return new Decoder();
}

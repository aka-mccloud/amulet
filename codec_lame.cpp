#include "codec_lame.hpp"

CodecLame::CodecLame(CodecProperties & props) :
    properties(props) {

}

Decoder *CodecLame::getDecoder() {

    return NULL;
}

Encoder * CodecLame::getEncoder() {

    return new Encoder(properties);
}

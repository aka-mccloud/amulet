#include "encoder.hpp"
#include "codec_lame.hpp"

CodecLame::CodecLame(CodecProperties & props) :
    properties(props) {

}

IDecoderProcess * CodecLame::getDecoder() {

    return NULL;
}

IEncoderProcess * CodecLame::getEncoder() {

    return new Encoder(properties);
}

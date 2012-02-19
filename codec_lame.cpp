#include "codec_lame.hpp"

CodecLame::CodecLame() {
}

Coder * CodecLame::getCodec() {

    return new Coder();
}

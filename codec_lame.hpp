#ifndef CODEC_LAME_HPP
#define CODEC_LAME_HPP

#include "icodec_provider.hpp"

class CodecLame : public ICodecProvider {

private:
    CodecProperties properties;

public:
    CodecLame(CodecProperties & props);
    IDecoderProcess * getDecoder();
    IEncoderProcess * getEncoder();

};

#endif // CODEC_LAME_HPP

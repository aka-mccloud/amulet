#ifndef CODEC_FLAC_HPP
#define CODEC_FLAC_HPP

#include "icodec_provider.hpp"

class CodecFlac : public ICodecProvider {

private:
    CodecProperties properties;

public:
    explicit CodecFlac(CodecProperties & props);
    virtual ~CodecFlac() {}

    IDecoderProcess * getDecoder();
    IEncoderProcess * getEncoder();

};

#endif // CODEC_FLAC_HPP

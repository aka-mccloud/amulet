#ifndef CODEC_PROVIDER_HPP
#define CODEC_PROVIDER_HPP

#include "icodec_provider.hpp"

class CodecProvider : public ICodecProvider {

public:
    explicit CodecProvider();
    virtual ~CodecProvider() {}

    IDecoderProcess * getDecoder();
    IEncoderProcess * getEncoder();

};

#endif // CODEC_PROVIDER_HPP

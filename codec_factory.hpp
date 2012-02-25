#ifndef CODEC_FACTORY_HPP
#define CODEC_FACTORY_HPP

#include "decoder.hpp"
#include "encoder.hpp"
#include "codec_flac.hpp"
#include "codec_lame.hpp"

class CodecFactory {

private:
    CodecMap codecMap;

public:
    CodecFactory(CodecProperties & props);
    virtual ~CodecFactory();

    Decoder * getDecoderForType(const QString & type);
    Encoder * getEncoderForType(const QString & type);

};

#endif // CODEC_FACTORY_HPP

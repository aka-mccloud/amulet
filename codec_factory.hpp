#ifndef CODEC_FACTORY_HPP
#define CODEC_FACTORY_HPP

#include "idecoder_process.hpp"
#include "iencoder_process.hpp"
#include "codec_flac.hpp"
#include "codec_lame.hpp"

class CodecFactory {

private:
    CodecMap codecMap;

public:
    CodecFactory(CodecProperties & props);
    virtual ~CodecFactory();

    IDecoderProcess * getDecoderForType(const QString & type);
    IEncoderProcess * getEncoderForType(const QString & type);

};

#endif // CODEC_FACTORY_HPP

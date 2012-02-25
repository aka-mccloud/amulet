#ifndef ICODEC_PROVIDER_H
#define ICODEC_PROVIDER_H

#include <QMap>

#include "codec_properties.hpp"
#include "decoder.hpp"
#include "encoder.hpp"

class ICodecProvider {

public:
//    virtual ICodecProvider(CodecProperties & props) = 0;
    virtual Decoder * getDecoder() = 0;
    virtual Encoder * getEncoder() = 0;

};

typedef QMap<QString, ICodecProvider *> CodecMap;

#endif // ICODEC_PROVIDER_H

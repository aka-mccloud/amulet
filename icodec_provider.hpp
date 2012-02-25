#ifndef ICODEC_PROVIDER_H
#define ICODEC_PROVIDER_H

#include <QMap>

#include "codec_properties.hpp"
#include "idecoder_process.hpp"
#include "iencoder_process.hpp"

class ICodecProvider {

public:
//    virtual ICodecProvider(CodecProperties & props) = 0;
    virtual ~ICodecProvider() {}

    virtual IDecoderProcess * getDecoder() = 0;
    virtual IEncoderProcess * getEncoder() = 0;

};

typedef QMap<QString, ICodecProvider *> CodecMap;

#endif // ICODEC_PROVIDER_H

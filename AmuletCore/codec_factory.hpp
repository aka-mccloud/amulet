#ifndef CODEC_FACTORY_HPP
#define CODEC_FACTORY_HPP

#include "idecoder_process.hpp"
#include "iencoder_process.hpp"
#include "plugins_provider.hpp"

class CodecFactory {

private:
    CodecMap codecMap;
    PluginsProvider plugins;

public:
    explicit CodecFactory();
    virtual ~CodecFactory();

    IDecoderProcess * getDecoderForType(const QString & type);
    IEncoderProcess * getEncoderForType(const QString & type);

};

#endif // CODEC_FACTORY_HPP

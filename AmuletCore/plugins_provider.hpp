#ifndef PLUGINS_PROVIDER_HPP
#define PLUGINS_PROVIDER_HPP

#include "icodec_provider.hpp"

class PluginsProvider {

    CodecMap codecMap;

public:
    explicit PluginsProvider();
    virtual ~PluginsProvider() {}

    const CodecMap & getCodecMap();

};

#endif // PLUGINS_PROVIDER_HPP

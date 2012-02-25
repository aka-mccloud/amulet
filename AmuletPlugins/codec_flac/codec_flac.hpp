#ifndef CODEC_FLAC_HPP
#define CODEC_FLAC_HPP

#include <QObject>
#include <QWidget>
#include <QStringList>

#include "icodec_plugin.hpp"
#include "icodec_provider.hpp"

class CodecFlac : public ICodecPlugin {

    Q_OBJECT
    Q_INTERFACES(ICodecPlugin)

private:
    ICodecProvider * codecProvider;
    QStringList formats;

public:
    explicit CodecFlac();
    virtual ~CodecFlac() {}

    QStringList getFromats();
    ICodecProvider * getCodec();
    QWidget * getWidget();

};

#endif // CODEC_FLAC_HPP

#ifndef CODEC_LAME_HPP
#define CODEC_LAME_HPP

#include <QObject>
#include <QWidget>
#include <QStringList>

#include "icodec_plugin.hpp"
#include "icodec_provider.hpp"

class CodecLame : public ICodecPlugin {

    Q_OBJECT
    Q_INTERFACES(ICodecPlugin)

private:
    ICodecProvider * codecProvider;
    QStringList formats;

public:
    explicit CodecLame();
    virtual ~CodecLame() {}

    QStringList getFromats();
    ICodecProvider * getCodec();
    QWidget * getWidget();

};

#endif // CODEC_LAME_HPP

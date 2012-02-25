#ifndef ICODEC_PLUGIN_HPP
#define ICODEC_PLUGIN_HPP

#include <QObject>
#include <QStringList>
#include <QtGui/QWidget>

#include "icodec_provider.hpp"

class ICodecPlugin : public QObject {

public:
    virtual ~ICodecPlugin() {}

    virtual QStringList getFromats() = 0;
    virtual ICodecProvider * getCodec() = 0;
    virtual QWidget * getWidget() = 0;

};

Q_DECLARE_INTERFACE(ICodecPlugin, "org.amulet.ICodecPlugin")

#endif // ICODEC_PLUGIN_HPP

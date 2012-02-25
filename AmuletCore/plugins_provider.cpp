#include <QCoreApplication>
#include <QPluginLoader>
#include <QObject>
#include <QDebug>
#include <QDir>

#include "icodec_plugin.hpp"
#include "plugins_provider.hpp"

PluginsProvider::PluginsProvider() {
    QDir pluginsDir = QDir(QCoreApplication::instance()->applicationDirPath());
    pluginsDir.cd("../AmuletPlugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        if (!loader.load()) {
            qDebug() << loader.errorString();
        } else {
            ICodecPlugin * plugin = qobject_cast<ICodecPlugin *>(loader.instance());
            if (plugin) {
                foreach(QString format, plugin->getFromats()) {
                    codecMap.insert(format, plugin->getCodec());
                }
            }
        }
    }
}

const CodecMap & PluginsProvider::getCodecMap() {

    return codecMap;
}

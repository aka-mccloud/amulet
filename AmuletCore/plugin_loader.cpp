/**************************************************************************
 *                                                                        *
 *  Copyright (C) 2012 by Yura Ivanov <yura.i1507@gmail.com>              *
 *                                                                        *
 *  This file is part of Amulet audio converter.                          *
 *                                                                        *
 *  Amulet is free software: you can redistribute it and/or modify        *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  Amulet is distributed in the hope that it will be useful,             *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with Amulet.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                        *
 **************************************************************************/

#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include <QDir>

#include "plugin_loader.hpp"

PluginLoader PluginLoader::pluginsLoader;

PluginLoader::PluginLoader() {
    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
            pluginsDir.cd("../AmuletPlugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader plugin(pluginsDir.absoluteFilePath(fileName));
        ICodecPlugin * codecPlugin = qobject_cast<ICodecPlugin *>(plugin.instance());
        if (codecPlugin) {
            foreach(QString format, codecPlugin->getFromats()) {
                pluginMap.insert(format, codecPlugin);
            }
        } else {
            qDebug() << plugin.errorString();
        }
    }
}

PluginLoader * PluginLoader::instance() {

    return &pluginsLoader;
}

CodecMap PluginLoader::getCodecMap() {
    CodecMap codecMap;
    PluginMap::const_iterator it;
    for (it = pluginMap.begin(); it != pluginMap.end(); ++it) {
        codecMap.insert(it.key(), it.value()->getCodec());
    }

    return codecMap;
}

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

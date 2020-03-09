/**************************************************************************
 *                                                                        *
 *  Copyright (C) 2020 by Yurii Ivanov <yivanov00@gmail.com>              *
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

#include <QPluginLoader>
#include <QDebug>
#include <QDir>

#include "plugin_loader.hpp"

PluginLoader PluginLoader::pluginsLoader;

PluginLoader::PluginLoader()
{
//     QStringList dirs = QString(qgetenv("XDG_DATA_DIRS")).split(':', QString::SkipEmptyParts);
    QStringList dirs = QString("../AmuletPlugins").split(':', QString::SkipEmptyParts);

    foreach (QString dir, dirs) {
        QDir pluginsDir = QDir(dir);
        pluginsDir.cd("amulet/plugins");

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
}

PluginLoader * PluginLoader::instance()
{
    return &pluginsLoader;
}

CodecMap PluginLoader::getCodecMap()
{
    CodecMap codecMap;
    PluginMap::const_iterator it;

    for (it = pluginMap.begin(); it != pluginMap.end(); ++it)
        codecMap.insert(it.key(), it.value()->getCodec());

    return codecMap;
}

QStringList PluginLoader::getFormats()
{
    return pluginMap.keys();
}

QList<QWidget *> PluginLoader::getWidgets()
{
    QList<QWidget *> list;
    PluginMap::const_iterator it;

    for (it = pluginMap.begin(); it != pluginMap.end(); ++it)
        list.append(it.value()->getWidget());

    return list;
}

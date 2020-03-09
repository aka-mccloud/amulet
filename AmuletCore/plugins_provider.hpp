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

#ifndef PLUGINS_PROVIDER_HPP
#define PLUGINS_PROVIDER_HPP

#include "AmuletCore_global.hpp"

#include "icodec_provider.hpp"
#include "plugin_loader.hpp"

class AMULETCORESHARED_EXPORT PluginsProvider
{

private:
    PluginLoader * pluginsLoader;
    CodecMap codecMap;

public:
    explicit PluginsProvider();
    virtual ~PluginsProvider() {}

    CodecMap getCodecMap();

};

#endif // PLUGINS_PROVIDER_HPP

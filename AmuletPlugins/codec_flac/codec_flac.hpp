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

#ifndef CODEC_FLAC_HPP
#define CODEC_FLAC_HPP

#include <QObject>
#include <QWidget>
#include <QStringList>

#include "icodec_plugin.hpp"

class CodecFlac : public ICodecPlugin
{

    Q_OBJECT
    Q_INTERFACES(ICodecPlugin)
    Q_PLUGIN_METADATA(IID "org.amulet.codec_flac" FILE "codec_flac.json")


private:
    ICodecProvider * codecProvider;
    QStringList formats;

public:
    explicit CodecFlac();
    virtual ~CodecFlac() {}

    QStringList getFromats();
    ICodecProvider * getCodec();
    ICodecWidget * getWidget();

};

#endif // CODEC_FLAC_HPP

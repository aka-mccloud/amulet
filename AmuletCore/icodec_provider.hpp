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

#ifndef ICODEC_PROVIDER_HPP
#define ICODEC_PROVIDER_HPP

#include <QMap>

#include "AmuletCore_global.hpp"

#include "codec_properties.hpp"
#include "idecoder_process.hpp"
#include "iencoder_process.hpp"

class AMULETCORESHARED_EXPORT ICodecProvider
{

public:
    virtual ~ICodecProvider() {}

    virtual IDecoderProcess * getDecoder() = 0;
    virtual IEncoderProcess * getEncoder() = 0;

};

typedef QMap<QString, ICodecProvider *> CodecMap;

Q_DECLARE_INTERFACE(ICodecProvider, "org.amulet.ICodecProvider")

#endif // ICODEC_PROVIDER_HPP

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

#include <QWidget>

#include "AmuletCore_global.hpp"

#include "codec_properties.hpp"

#ifndef ICODEC_WIDGET_HPP
#define ICODEC_WIDGET_HPP

class AMULETCORESHARED_EXPORT ICodecWidget : public QWidget
{

public:
    virtual ~ICodecWidget() {}

    virtual CodecProperties getProperties() = 0;

};

Q_DECLARE_INTERFACE(ICodecWidget, "org.amulet.ICodecWidget")

#endif // ICODEC_WIDGET_HPP

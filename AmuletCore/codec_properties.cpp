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

#include "codec_properties.hpp"

CodecProperties::CodecProperties() {
}

QStringList CodecProperties::toStringList(const QMap<Options, QString> & options) const {
    QStringList codecProps;

    QList<Options> keys = values.keys();
    QList<Options>::iterator it;

    for (it = keys.begin(); it != keys.end(); ++it) {
        codecProps += options[*it];
        codecProps += values[*it];
    }

    return codecProps;
}

QString & CodecProperties::operator [](CodecProperties::Options option) {

    return values[option];
}

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

#ifndef CODEC_PROPERTIES_HPP
#define CODEC_PROPERTIES_HPP

#include <QString>
#include <QStringList>
#include <QMap>

class CodecProperties {

public:
    enum Options {
        BITRATE,
        SAMPLERATE,
        LOWPASS
    };

private:
    QMap<Options, QString> values;

public:
    explicit CodecProperties();
    virtual ~CodecProperties() {}

//    QString toString();
    QStringList toStringList(const QMap<Options, QString> & options) const;

    QString & operator [](Options option);

};

#endif // CODEC_PROPERTIES_HPP
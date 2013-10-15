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

#ifndef IENCODER_PROCESS_HPP
#define IENCODER_PROCESS_HPP

#include <QObject>
#include <QString>
#include <QProcess>

#include "AmuletCore_global.hpp"

#include "codec_properties.hpp"

class AMULETCORESHARED_EXPORT IEncoderProcess
{

public:
    virtual ~IEncoderProcess() {}

    virtual void setOutputFile(const QString & fileName) = 0;
    virtual void setProperties(const CodecProperties & props) = 0;
    virtual QProcess * getProcessInstance() = 0;
    virtual QObject * getObject() = 0;

//public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

//signals:
    virtual void finished() = 0;

};

Q_DECLARE_INTERFACE(IEncoderProcess, "org.amulet.IEncoderProcess")

#endif // IENCODER_PROCESS_HPP

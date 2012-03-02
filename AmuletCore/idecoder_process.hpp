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

#ifndef IDECODER_PROCESS_H
#define IDECODER_PROCESS_H

#include <QObject>
#include <QString>
#include <QProcess>

class IDecoderProcess {

public:
    virtual ~IDecoderProcess() {}

    virtual void setInputFile(const QString & fileName) = 0;
    virtual QProcess * getProcessInstance() = 0;
    virtual QObject * getObject() = 0;

//public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

//signals:
    virtual void progress(int) = 0;
    virtual void finished() = 0;

};

Q_DECLARE_INTERFACE(IDecoderProcess, "org.amulet.IDecoderProcess")

#endif // IDECODER_PROCESS_H
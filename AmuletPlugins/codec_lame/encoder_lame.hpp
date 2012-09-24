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

#ifndef ENCODER_LAME_HPP
#define ENCODER_LAME_HPP

#include <QObject>

#include "iencoder_process.hpp"

#define coderName "lame"
#define extension "mp3"

class EncoderLame : public QObject, public IEncoderProcess
{

    Q_OBJECT
    Q_INTERFACES(IEncoderProcess)

private:
    QMap<CodecProperties::Options, QString> options;
    QProcess * process;
    QStringList args;
    QString inputFile;
    QString outputFile;
    bool terminated;

private slots:
    void finished(int);

public:
    explicit EncoderLame(QObject * parent = 0);
    virtual ~EncoderLame();

    void setProperties(const CodecProperties & props);
    void setOutputFile(const QString & fileName);
    QProcess * getProcessInstance();
    QObject * getObject();

public slots:
    void start();
    void stop();

signals:
    void finished();

};

#endif // ENCODER_LAME_HPP

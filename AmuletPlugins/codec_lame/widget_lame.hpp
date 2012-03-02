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

#ifndef WIDGET_LAME_HPP
#define WIDGET_LAME_HPP

#include "icodec_widget.hpp"
#include "codec_properties.hpp"

namespace Ui {
class WidgetLame;
}

class WidgetLame : public ICodecWidget {

    Q_OBJECT
    Q_INTERFACES(ICodecWidget)

private:
    Ui::WidgetLame * ui;

private slots:
    void on_qualityEdit_valueChanged(int value);
    void on_qualitySlider_valueChanged(int value);
    void on_selectBox_currentIndexChanged(int index);

public:
    explicit WidgetLame();
    virtual ~WidgetLame();

    CodecProperties getProperties();

};

#endif // WIDGET_LAME_HPP

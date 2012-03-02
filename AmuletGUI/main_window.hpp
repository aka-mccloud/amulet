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

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QFileInfoList>
#include <QDir>

#include "converter_service.hpp"

#include "queue_model.hpp"
#include "plugin_loader.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

private:
    Ui::MainWindow * ui;
    PluginLoader * pluginLoader;
    ConverterService converterService;
    QueueModel queueModel;
    QStringList filter;
    QString path;

    void scanSubDirs(const QDir & dir, QFileInfoList * fileList);

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void on_actionAddFiles_triggered();
    void on_actionAddDir_triggered();
    void on_filesDropped(const QMimeData * mimeData);
    void on_actionConvert_triggered();
    void on_formatBox_currentIndexChanged(int index);

};

#endif // MAIN_WINDOW_HPP

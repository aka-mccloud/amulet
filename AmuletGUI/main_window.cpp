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

#include <QFileDialog>

#include "main_window.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    queueModel(this) {
    ui->setupUi(this);
    pluginLoader = PluginLoader::instance();
    ui->formatBox->addItems(pluginLoader->getFormats());
    ui->formatBox->setCurrentIndex(0);
    foreach (QWidget * widget, pluginLoader->getWidgets()) {
        ui->stackedWidget->addWidget(widget);
    }

    connect(&converterService,
            SIGNAL(progressChanged()),
            &queueModel,
            SLOT(updateProgress()));

    ui->queueTableView->setModel(&queueModel);
    filter << "*.flac" << "*.mp3";
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::scanSubDirs(const QDir & dir, QFileInfoList * fileList) {
    QFileInfoList files = dir.entryInfoList(filter, QDir::Files);
    fileList->append(files);

    QStringList dirs = dir.entryList(filter, QDir::AllDirs | QDir::NoDotAndDotDot);
    if (!dirs.empty()) {
        foreach (QString dirName, dirs) {
            QDir newDir(dir);
            newDir.cd(dirName);
            scanSubDirs(newDir, fileList);
        }
    }
}

void MainWindow::on_actionAddFiles_triggered() {
    QString filter("Supperted formats (");
    foreach (QString format, this->filter) {
        filter += format + " ";
    }
    filter += ");;All files(*.*)";

    QStringList fileList = QFileDialog::getOpenFileNames(
                this, tr("Select file(s)"), path, filter);

    QFileInfoList list;
    foreach (QString file, fileList) {
        list.append(QFileInfo(file));
    }

    if (!list.isEmpty()) {
        path = list.first().absolutePath();
        queueModel.append(list);
    }
}

void MainWindow::on_actionAddDir_triggered() {
    path = QFileDialog::getExistingDirectory(this, tr("Select dir"), path);

    if (!path.isEmpty()) {
        QDir dir(path);

        QFileInfoList fileList;
        scanSubDirs(dir, &fileList);

        queueModel.append(fileList);
    }
}

void MainWindow::on_actionConvert_triggered() {
    CodecProperties properties = qobject_cast<ICodecWidget *>(
                ui->stackedWidget->currentWidget())->getProperties();

    converterService.setCodecProperties(properties);
    converterService.setMaxThreadCount(3);
    converterService.setOutDir(QDir(QApplication::applicationDirPath()));
    converterService.setQueue(queueModel.getQueue());
    converterService.setOutFormat(ui->formatBox->currentText());
    converterService.start();
}

void MainWindow::on_formatBox_currentIndexChanged(int index) {
    ui->stackedWidget->setCurrentIndex(index);
}

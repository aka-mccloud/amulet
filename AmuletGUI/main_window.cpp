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

#include <QDesktopServices>
#include <QFileDialog>
#include <QUrl>

#include <math.h>

#include "properties_dialog.hpp"
#include "about_dialog.hpp"
#include "main_window.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings("Amulet"),
    queueModel(this) {
    ui->setupUi(this);
    pluginLoader = PluginLoader::instance();
    ui->formatBox->addItems(pluginLoader->getFormats());
    ui->formatBox->setCurrentIndex(0);
    foreach (QWidget * widget, pluginLoader->getWidgets()) {
        ui->stackedWidget->addWidget(widget);
    }

    defaultPath = settings.value("MainWindow/source_path", QDesktopServices::storageLocation(
                                     QDesktopServices::HomeLocation)).toString();

    connect(&converterService,
            SIGNAL(progressChanged()),
            &queueModel,
            SLOT(updateProgress()));
    connect(&converterService,
            SIGNAL(progressChanged()),
            SLOT(changeProgress()));
    connect(ui->queueTableView,
            SIGNAL(filesDropped(const QMimeData *)),
            SLOT(on_filesDropped(const QMimeData *)));

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
                this, tr("Select file(s)"), defaultPath, filter);

    QFileInfoList list;
    foreach (QString file, fileList) {
        list.append(QFileInfo(file));
    }

    if (!list.isEmpty()) {
        defaultPath = list.first().absolutePath();
        queueModel.append(list);
    }
}

void MainWindow::on_actionAddDir_triggered() {
    defaultPath = QFileDialog::getExistingDirectory(this, tr("Select dir"), defaultPath);

    if (!defaultPath.isEmpty()) {
        QDir dir(defaultPath);

        QFileInfoList fileList;
        scanSubDirs(dir, &fileList);

        queueModel.append(fileList);
    }
}

void MainWindow::on_filesDropped(const QMimeData * mimeData) {
    QFileInfoList fileList;
    QList<QUrl> urlList = mimeData->urls();

    foreach (QUrl url, urlList) {
        QFileInfo file(url.toLocalFile());
        if ((file.isFile()) && filter.contains("*." + file.suffix())) {
            fileList.append(file);
        }
        if (file.isDir()) {
            scanSubDirs(QDir(url.toLocalFile()), &fileList);
        }
    }

    queueModel.append(fileList);
}

void MainWindow::on_actionClearList_triggered() {
    queueModel.clear();
}

void MainWindow::on_actionConvert_triggered() {
    CodecProperties properties = qobject_cast<ICodecWidget *>(
                ui->stackedWidget->currentWidget())->getProperties();
    QString targetPath;
    if (settings.value("Properties/path", false).toBool()) {
        targetPath = settings.value("Properties/target_path",
            QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
    }
    int maxThreadCount = settings.value("Properties/threads", 1).toInt();

    converterService.setCodecProperties(properties);
    converterService.setMaxThreadCount(maxThreadCount);
    converterService.setOutPath(targetPath);
    converterService.setQueue(queueModel.getQueue());
    converterService.setOutFormat(ui->formatBox->currentText());
    converterService.start();
}

void MainWindow::on_formatBox_currentIndexChanged(int index) {
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::on_actionProperties_triggered() {
    PropertiesDialog dialog(& settings, this);
    dialog.exec();
}

void MainWindow::on_actionAbout_triggered() {
    AboutDialog about(this);
    about.exec();
}

void MainWindow::changeProgress() {
    ui->progressBar->setValue(round(queueModel.getQueue()->countProgress()));
}

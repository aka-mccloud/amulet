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

#if QT_MAJOR_VERSION > 4
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif
#include <QFileDialog>
#include <QUrl>

#include <cmath>

#include "properties_dialog.hpp"
#include "about_dialog.hpp"
#include "main_window.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), settings("Amulet"), queueModel(this)
{
    pluginLoader = PluginLoader::instance();

    ui->setupUi(this);

    foreach (QWidget * widget, pluginLoader->getWidgets())
        ui->stackedWidget->addWidget(widget);

    ui->formatBox->addItems(pluginLoader->getFormats());
    ui->formatBox->setCurrentIndex(ui->formatBox->findText(settings.value("MainWindow/format", "flac").toString()));
    ui->queueTreeView->setModel(&queueModel);
    ui->queueTreeView->addAction(ui->actionDelete);
    ui->actionConvert->setIcon(QIcon::fromTheme("view-refresh"));
    ui->actionAddFiles->setIcon(QIcon::fromTheme("document-new"));
    ui->actionAddDir->setIcon(QIcon::fromTheme("folder-new"));
    ui->actionClearList->setIcon(QIcon::fromTheme("edit-clear"));
    ui->actionProperties->setIcon(QIcon::hasThemeIcon("configure") ? QIcon::fromTheme("configure") : QIcon::fromTheme("gtk-preferences"));
    ui->actionHelp->setIcon(QIcon::fromTheme("help-contents"));
    ui->actionAbout->setIcon(QIcon::fromTheme("help-about"));
    toggleToolBar(true);

#if QT_MAJOR_VERSION > 4
    defaultPath = settings.value("MainWindow/source_path", QStandardPaths::standardLocations(QStandardPaths::HomeLocation)).toString();
#else
    defaultPath = settings.value("MainWindow/source_path", QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
#endif

    connect(&converterService,
            SIGNAL(progressChanged()),
            &queueModel,
            SLOT(updateProgress()));
    connect(&converterService,
            SIGNAL(progressChanged()),
            SLOT(changeProgress()));
    connect(&converterService,
            SIGNAL(finished()),
            SLOT(finished()));
    connect(ui->queueTreeView,
            SIGNAL(filesDropped(const QMimeData *)),
            SLOT(filesDropped(const QMimeData *)));

    foreach (QString format, pluginLoader->getFormats())
        filter << "*." + format;
}

MainWindow::~MainWindow()
{
    settings.setValue("MainWindow/source_path", defaultPath);
    settings.setValue("MainWindow/format", ui->formatBox->currentText());

    delete ui;
}

void MainWindow::scanSubDirs(const QDir & dir, QFileInfoList * fileList)
{
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

void MainWindow::toggleToolBar(bool state)
{
    ui->actionConvert->setText(state ? tr("Convert") : tr("Stop"));
    ui->actionConvert->setIcon(state ? QIcon::fromTheme("view-refresh") : QIcon::fromTheme("dialog-cancel"));
    ui->actionAddFiles->setEnabled(state);
    ui->actionAddDir->setEnabled(state);
    ui->actionClearList->setEnabled(state);
    ui->actionProperties->setEnabled(state);
    ui->actionDelete->setEnabled(state);
}

void MainWindow::on_actionAddFiles_triggered()
{
    QString filter("Supperted formats (");

    foreach (QString format, this->filter)
        filter += format + " ";
    filter += ");;All files(*.*)";

    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Select file(s)"), defaultPath, filter);
    QFileInfoList list;

    foreach (QString file, fileList)
        list.append(QFileInfo(file));

    if (!list.isEmpty()) {
        defaultPath = list.first().absolutePath();
        queueModel.append(list);
    }
}

void MainWindow::on_actionAddDir_triggered()
{
    defaultPath = QFileDialog::getExistingDirectory(this, tr("Select dir"), defaultPath);

    if (!defaultPath.isEmpty()) {
        QDir dir(defaultPath);
        QFileInfoList fileList;

        scanSubDirs(dir, &fileList);

        queueModel.append(fileList);
    }
}

void MainWindow::on_actionClearList_triggered()
{
    queueModel.clear();
}

void MainWindow::on_actionConvert_triggered()
{
    if (converterService.isRunning()) {
        toggleToolBar(true);
        converterService.stop();
    } else {
        toggleToolBar(false);
        CodecProperties properties = qobject_cast<ICodecWidget *>(ui->stackedWidget->currentWidget())->getProperties();
        converterService.setSettings(settings);
        converterService.setCodecProperties(properties);
        converterService.setQueue(queueModel.getQueue());
        converterService.setOutFormat(ui->formatBox->currentText());
        converterService.start();
    }
}

void MainWindow::on_actionDelete_triggered()
{
    QModelIndexList indexList = ui->queueTreeView->selectionModel()->selectedIndexes();
    if (!indexList.isEmpty())
        queueModel.delIndexes(indexList);
}

void MainWindow::on_actionProperties_triggered()
{
    PropertiesDialog dialog(&settings, this);
    dialog.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog about(this);
    about.exec();
}

void MainWindow::on_formatBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::changeProgress()
{
    ui->progressBar->setValue(floor(queueModel.getQueue()->countProgress()));
}

void MainWindow::filesDropped(const QMimeData * mimeData)
{
    QFileInfoList fileList;
    QList<QUrl> urlList = mimeData->urls();

    foreach (QUrl url, urlList) {
        QFileInfo file(url.toLocalFile());

        if ((file.isFile()) && filter.contains("*." + file.suffix()))
            fileList.append(file);
        if (file.isDir())
            scanSubDirs(QDir(url.toLocalFile()), &fileList);
    }

    queueModel.append(fileList);
}

void MainWindow::finished()
{
    toggleToolBar(true);
}

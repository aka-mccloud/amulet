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
#include <QStandardPaths>

#include "properties_dialog.hpp"
#include "ui_properties_dialog.h"

PropertiesDialog::PropertiesDialog(QSettings * settings, QWidget * parent)
    : QDialog(parent), ui(new Ui::PropertiesDialog), settings(settings), languageChanged(false)
{
    ui->setupUi(this);

    settings->beginGroup("Properties");

    targetPath = settings->value("target_path", QStandardPaths::standardLocations(QStandardPaths::HomeLocation)).toString();

    if (settings->value("path", false).toBool()) {
        ui->pathRadioButton->setChecked(true);
        ui->selectButton->setEnabled(true);
        ui->pathEdit->setEnabled(true);
    }
    ui->pathEdit->setText(targetPath);
    ui->threadsBox->setValue(settings->value("threads", 1).toInt());
    ui->languageBox->setCurrentIndex(ui->languageBox->findText(settings->value("language", "en").toString()));
    settings->endGroup();
}

PropertiesDialog::~PropertiesDialog()
{
    delete ui;
}

void PropertiesDialog::on_samePathRadioButton_clicked()
{
    ui->selectButton->setEnabled(false);
    ui->pathEdit->setEnabled(false);
}

void PropertiesDialog::on_pathRadioButton_clicked()
{
    ui->selectButton->setEnabled(true);
    ui->pathEdit->setEnabled(true);
}

void PropertiesDialog::on_selectButton_clicked()
{
    QString targetPath = QFileDialog::getExistingDirectory(this, tr("Select dir"), this->targetPath);

    if (!targetPath.isEmpty())
        ui->pathEdit->setText(targetPath);
}

void PropertiesDialog::on_buttonBox_accepted()
{
    settings->beginGroup("Properties");
    settings->setValue("path", ui->pathRadioButton->isChecked());
    settings->setValue("target_path", ui->pathEdit->text());
    settings->setValue("threads", ui->threadsBox->value());
    settings->setValue("language", ui->languageBox->currentText());
    settings->endGroup();
}

void PropertiesDialog::on_languageBox_currentIndexChanged(int)
{
    languageChanged = true;
}

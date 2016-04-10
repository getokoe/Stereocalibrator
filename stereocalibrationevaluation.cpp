/*******************************************************************************
 *
 *   Copyright (C) 2016 by Tom Koeppchen
 *   gtkoeppchen (at) googlemail (dot) com
 *   This file is part of Stereocalibrator.
 *
 *   Stereocalibrator is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Stereocalibrator is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with Stereocalibrator. If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include "stereocalibrationevaluation.h"

/**
 * Constructor
 * @param stereo
 * @param parent
 */
StereoCalibrationEvaluation::StereoCalibrationEvaluation(
        scc::StereoCalibration *stereo, QWidget *parent) :
    QWidget(parent) {
    qDebug() << "StereoCalibrationEvaluation(QTabWidget *parent)";
    stereoCalibration = stereo;
    setupLayout();
}

/**
 * Destructor.
 */
StereoCalibrationEvaluation::~StereoCalibrationEvaluation() {
    qDebug() << "~StereoCalibrationEvaluation()";
}

/**
 * Sets up the layout.
 */
void StereoCalibrationEvaluation::setupLayout() {
    qDebug() << "CameraCalibrationEvaluation::setupLayout()";
    QHBoxLayout *mainLayout = new QHBoxLayout;
    imagePreview = new QScrollArea;
    setImagePreviewLayout(imagePreview);
    mainLayout->addWidget(imagePreview);
    dataPreview = new QWidget;
    setDataPreviewLayout(dataPreview);
    mainLayout->addWidget(dataPreview);
    setLayout(mainLayout);
}

/**
 * Sets up the layout for the image preview area.
 * @param picPreview The widget to set up the layout for.
 */
void StereoCalibrationEvaluation::setImagePreviewLayout(
        QScrollArea *picPreview) {
    qDebug() << "CameraCalibrationEvaluation::setImagePreviewLayout("
             << "QScrollArea *picPreview)";
    picPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    picPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    imagePreviewWidget = new QWidget;
    picPreview->setWidget(imagePreviewWidget);
    imagePreviewLayout = new QVBoxLayout(imagePreviewWidget);
    imagePreviewLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    loadImagesIntoPreview(stereoCalibration->getTargetImageStrings());
}

/**
 * Sets up the layout for the data preview area.
 * @param dPreview The widget to set up the layout for.
 */
void StereoCalibrationEvaluation::setDataPreviewLayout(QWidget *dPreview) {
    qDebug() << "CameraCalibrationEvaluation::setDataPreviewLayout("
             << "QScrollArea *picPreview)";
    QVBoxLayout *dataPreviewLayout = new QVBoxLayout(dPreview);
    results = new QPlainTextEdit;
    results->setReadOnly(true);
    results->setMinimumHeight(1);
    results->setMinimumWidth(1);
    QPalette palette;
    palette.setColor(QPalette::Base,Qt::black);
    palette.setColor(QPalette::Text,Qt::white);
    results->setPalette(palette);
    dataPreviewLayout->addWidget(results);
    loadDataIntoResultPreview();
}

/**
 * Loads the data into the data preview area.
 */
void StereoCalibrationEvaluation::loadDataIntoResultPreview() {
    results->appendPlainText("Rotation matrix:\n");
    results->appendPlainText(QString::fromStdString(stereoCalibration->getRotationMatrixString()));
    results->appendPlainText("\nTranslation matrix:\n");
    results->appendPlainText(QString::fromStdString(stereoCalibration->getTranslationMatrixString()));
    results->appendPlainText("\nEssential  matrix:\n");
    results->appendPlainText(QString::fromStdString(stereoCalibration->getEssentialMatrixString()));
    results->appendPlainText("\nFundamental  matrix:\n");
    results->appendPlainText(QString::fromStdString(stereoCalibration->getFundamentalMatrixString()));
    results->appendPlainText("\nQ  matrix:\n");
    results->appendPlainText(QString::fromStdString(stereoCalibration->getQMatrixString()));
}

/**
 * Loads the given images from the system and places them as button into the
 * image preview area.
 * @param imageFiles Vector of string holding the path to the images to load.
 */
void StereoCalibrationEvaluation::loadImagesIntoPreview(
        std::vector<std::string> imageFiles) {
    qDebug() << "StereoCalibrationEvaluation::loadImagesIntoPreview("
             << "std::vector<std::string> imageFiles)";
    picPreviewMapper = new QSignalMapper();
    for (unsigned int i = 0; i < imageFiles.size(); i++) {
        tempPixmap = new QPixmap(QString::fromStdString(imageFiles.at(i)));
        *tempPixmap = tempPixmap->scaledToWidth(
                    imagePreview->viewport()->width() * 0.45);
        QPushButton *tempButton = new QPushButton;
        tempButton->setFlat(true);
        tempButton->setAutoFillBackground(true);
        tempButton->setIcon(QIcon(*tempPixmap));
        tempButton->setIconSize(QSize(tempPixmap->width(),
                                      tempPixmap->height()));
        imagePreviewLayout->addWidget(tempButton);
        connect(tempButton, SIGNAL(clicked()), picPreviewMapper, SLOT(map()));
        picPreviewMapper->setMapping(tempButton,
                                     QString::fromStdString(imageFiles.at(i)));
    }
    connect(picPreviewMapper, SIGNAL(mapped(const QString &)), this,
            SLOT(openMaxPicWindow(const QString &)));

}

/**
 * Opens a window containing the image found under the given path.
 * @param imagePath The path to the image a window is opened for.
 */
void StereoCalibrationEvaluation::openMaxPicWindow(const QString &imagePath) {
    qDebug() << "StereoCalibrationEvaluation::openMaxPicWindow(const QString "
                "&imagePath) ...";
    QScrollArea *sArea = new QScrollArea;
    QLabel *label = new QLabel;
    QPixmap *pixmap = new QPixmap(imagePath);
    label->setPixmap(*pixmap);
    sArea->setWidget(label);
    sArea->setWindowTitle(imagePath);
    sArea->showMaximized();
}

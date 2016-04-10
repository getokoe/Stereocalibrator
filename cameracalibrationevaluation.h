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

#ifndef CAMERACALIBRATIONEVALUATION_H
#define CAMERACALIBRATIONEVALUATION_H

#include <QtWidgets>
#include <vector>
#include <string>

#include "cameracalibration.h"

class CameraCalibrationEvaluation : public QWidget {
    Q_OBJECT

public:
    explicit CameraCalibrationEvaluation(scc::CameraCalibration *cam,
                                         QWidget *parent = 0);
    ~CameraCalibrationEvaluation();

signals:

public slots:

private slots:
    void openMaxPicWindow(const QString &imagePath);

private:
    scc::CameraCalibration *cameraCalibration;

    QScrollArea *imagePreview;
    QWidget *imagePreviewWidget;
    QVBoxLayout *imagePreviewLayout;

    QPixmap *tempPixmap;

    QSignalMapper *picPreviewMapper;

    QWidget *dataPreview;

    QPlainTextEdit *results;

    void setupLayout();
    void setImagePreviewLayout(QScrollArea *iPreview);
    void setDataPreviewLayout(QWidget *dPreview);
    void loadImagesIntoPreview(std::vector<std::string> imageFiles);
    void loadDataIntoResultPreview();
};

#endif // CAMERACALIBRATIONEVALUATION_H

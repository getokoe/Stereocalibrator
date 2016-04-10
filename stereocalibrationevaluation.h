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

#ifndef STEREOCALIBRATIONEVALUATION_H
#define STEREOCALIBRATIONEVALUATION_H

#include <QtWidgets>
#include <vector>
#include <string>

#include "stereocalibration.h"

class StereoCalibrationEvaluation : public QWidget {
    Q_OBJECT

public:
    explicit StereoCalibrationEvaluation(scc::StereoCalibration *stereo,
                                         QWidget *parent = 0);
    ~StereoCalibrationEvaluation();

signals:

public slots:

private slots:
    void openMaxPicWindow(const QString &imagePath);

private:
    scc::StereoCalibration *stereoCalibration;

    QScrollArea *imagePreview;
    QWidget *imagePreviewWidget;
    QVBoxLayout *imagePreviewLayout;

    QPixmap *tempPixmap;

    QSignalMapper *picPreviewMapper;

    QWidget *dataPreview;

    QPlainTextEdit *results;

    void setupLayout();
    void setImagePreviewLayout(QScrollArea *picPreview);
    void setDataPreviewLayout(QWidget *dPreview);
    void loadImagesIntoPreview(std::vector<std::string> imageFiles);
    void loadDataIntoResultPreview();
};

#endif // STEREOCALIBRATIONEVALUATION_H

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

#include "calibrationevaluation.h"

/**
 * Default constructor.
 * @param parent
 */
CalibrationEvaluation::CalibrationEvaluation(QWidget *parent) :
    QWidget(parent) {
    qDebug() << "CalibrationEvaluation(QTabWidget *parent):";
    setupLayout();
}

/**
 * Constructor.
 * @param left
 * @param right
 * @param stereo
 * @param parent
 */
CalibrationEvaluation::CalibrationEvaluation(scc::CameraCalibration *left,
                                             scc::CameraCalibration *right,
                                             scc::StereoCalibration *stereo,
                                             QWidget *parent) :
    QWidget(parent) {
    qDebug() << "CalibrationEvaluation(CameraCalibration *left,"
             << " CameraCalibration *right, StereoCalibration *stereo):";
    leftCam = left;
    rightCam = right;
    stereoCam = stereo;
    setupLayout();
}

/**
 * Destructor.
 */
CalibrationEvaluation::~CalibrationEvaluation() {
    qDebug() << "~CalibrationEvaluation():";
}

/**
 * Sets up the layout.
 */
void CalibrationEvaluation::setupLayout() {
    qDebug() << "setupLayout():";

    QHBoxLayout *mainLayout = new QHBoxLayout;
    tabWidget = new QTabWidget;
    tabWidget->addTab(new CameraCalibrationEvaluation(leftCam), "Left camera");
    tabWidget->addTab(new CameraCalibrationEvaluation(rightCam),
                      "Right camera");
    tabWidget->addTab(new StereoCalibrationEvaluation(stereoCam),
                      "Stereo camera");
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

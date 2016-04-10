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

#ifndef CALIBRATIONEVALUATION_H
#define CALIBRATIONEVALUATION_H

#include <QtWidgets>

#include "cameracalibration.h"
#include "cameracalibrationevaluation.h"
#include "stereocalibration.h"
#include "stereocalibrationevaluation.h"


class CalibrationEvaluation : public QWidget {
    Q_OBJECT

public:
    explicit CalibrationEvaluation(QWidget *parent = 0);
    explicit CalibrationEvaluation(scc::CameraCalibration *left,
                                   scc::CameraCalibration *right,
                                   scc::StereoCalibration *stereo,
                                   QWidget *parent = 0);
    ~CalibrationEvaluation();

signals:

public slots:

private slots:
    void setupLayout();

private:
    QTabWidget *tabWidget;

    scc::CameraCalibration *leftCam;
    scc::CameraCalibration *rightCam;
    scc::StereoCalibration *stereoCam;

};

#endif // CALIBRATIONEVALUATION_H

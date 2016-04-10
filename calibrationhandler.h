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

#ifndef CALIBRATIONHANDLER_H
#define CALIBRATIONHANDLER_H

#include <QPlainTextEdit>
#include <QListWidget>
#include <QCoreApplication>
#include <sstream>
#include <ctime>

#include "cameracalibration.h"
#include "stereocalibration.h"

class CalibrationHandler {

public:
    CalibrationHandler(QPlainTextEdit *logWindow, int blockSize, int blocksH,
                       int blocksV, QListWidget *leftSource,
                       QListWidget *rightSource);

    // Handle calibration
    bool handleStereoCalibration();

    scc::CameraCalibration* getLeftCam();
    scc::CameraCalibration* getRightCam();
    scc::StereoCalibration* getStereoCam();

    std::string print();

private:
    // User feedback var
    QPlainTextEdit *userLog;

    // Calibration vars
    scc::CameraCalibration *leftCam;
    scc::CameraCalibration *rightCam;
    scc::StereoCalibration *stereoCam;

    void handleCameraCalibration(scc::CameraCalibration *cam);

    std::vector<std::string> convertQListWidgetToVectorOfStrings(
                                                    QListWidget *listToConvert);
    void replaceLastLineOfUserLog(std::string line);
};

#endif // CALIBRATIONHANDLER_H

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

#include "calibrationhandler.h"

/**
 * Default constructor.
 * @param logWindow Element to show information to the user.
 * @param blockSize Size of the calibration pattern.
 * @param blocksH Number of calibration pattern elements in horizontal
 *                  direction.
 * @param blocksV Number of calibration pattern elements in vertical direction.
 * @param leftSource List of calibration source files for left camera.
 * @param rightSource List of calibration source files for right camera.
 */
CalibrationHandler::CalibrationHandler(QPlainTextEdit *logWindow,
                                       int blockSize,
                                       int blocksH,
                                       int blocksV,
                                       QListWidget *leftSource,
                                       QListWidget *rightSource) {
    userLog = logWindow;
    leftCam = new scc::CameraCalibration(blockSize, blocksH, blocksV,
                            convertQListWidgetToVectorOfStrings(leftSource),
                                    "left");
    rightCam = new scc::CameraCalibration(blockSize, blocksH, blocksV,
                            convertQListWidgetToVectorOfStrings(rightSource),
                                     "right");
    stereoCam = new scc::StereoCalibration();
}

/**
 * This function handles the whole calibration process. First of it starts the
 * two camera calibrations, if there are more than one image available.
 * Afterwards the stereo calibration will be done. It checks for matching images
 * and if there are enough the calibration is started. Then the rotation of
 * the images is checked and more images will be added if necessary. If so the
 * calibration will be re-run. The last part is saving the images and
 * calibration data.
 */
bool CalibrationHandler::handleStereoCalibration() {
    bool retVal = false;
    if (leftCam->getSourceImagesNo() > 1) {
        // handle camera calibration
        handleCameraCalibration(leftCam);
        handleCameraCalibration(rightCam);

        // handle stere calibration
        userLog->appendPlainText("\nStereo camera system calibration:");
        qApp->processEvents();
        stereoCam = new scc::StereoCalibration(leftCam, rightCam);
        userLog->appendPlainText("... stereo camera system initialized.");
        qApp->processEvents();

        // check for usable images
        unsigned int numberOfImages = stereoCam->checkForMatchingImages();
        std::stringstream ss;
        ss << numberOfImages << " pairs of images were found within the image lists used for camera calibration.";
        userLog->appendPlainText(QString::fromStdString(ss.str()));
        qApp->processEvents();

        // calibrate if enough images where found
        if (numberOfImages > 2) {
            double rms = stereoCam->calibrate(15);
            ss.str(std::string());
            ss.clear();
            ss << "RMS for stereo calibration: " << rms;
            userLog->appendPlainText(QString::fromStdString(ss.str()));
            qApp->processEvents();
            retVal = true;

            // check that there are more pictures than minimal needed
            if (stereoCam->getUsableSourceImageAmount() > 15) {

                // check for rotation in used images
                double minRotation = 60.0;
                ss.str(std::string());
                ss.clear();
                ss << "Checking used images for rotation over " << minRotation << " degrees ...";
                userLog->appendPlainText(QString::fromStdString(ss.str()));
                qApp->processEvents();
                if (!stereoCam->checkUsedImagesForRotation(minRotation)) {
                    ss.str(std::string());
                    ss.clear();
                    ss << "Used images have no rotation over " << minRotation << " degrees.";
                    replaceLastLineOfUserLog(ss.str());
                    int rotatedImagePos = stereoCam->checkForRotatedImage(minRotation);
                    if (rotatedImagePos != -1) {
                        stereoCam->addImageFromUseableToUsed(rotatedImagePos);
                        userLog->appendPlainText("Added image with desired rotation.");
                        qApp->processEvents();
                        rms = stereoCam->recalibrate();
                        ss.str(std::string());
                        ss.clear();
                        ss << "New RMS is : " << rms;
                        userLog->appendPlainText(QString::fromStdString(ss.str()));
                        qApp->processEvents();
                    } else {
                        userLog->appendPlainText("There is no image with desired rotation available.");
                        qApp->processEvents();
                    }
                } else {
                    ss.str(std::string());
                    ss.clear();
                    ss << "Used images have rotation over " << minRotation << " degrees.";
                    replaceLastLineOfUserLog(ss.str());
                }
            } else {
                userLog->appendPlainText("There are too few usable images to optimize stereo calibration.");
                qApp->processEvents();
            }

            // creating timestamp for saving
            time_t timeStamp;
            struct tm *timeInfo;
            char timeStr[80];
            time(&timeStamp);
            timeInfo = localtime(&timeStamp);
            strftime(timeStr, 80, "%Y-%m-%d_%H-%M-%S", timeInfo);

            // saving data
            userLog->appendPlainText("Saving stereo calibration data...");
            qApp->processEvents();
            ss.str(std::string());
            ss.clear();
            ss << "stereo-calibration_" << timeStr;
            stereoCam->saveData(ss.str());
            replaceLastLineOfUserLog("Saving stereo calibration data... Done.");
            qApp->processEvents();

        } else {
            userLog->appendPlainText("There are too few usable images for stereo calibration.");
            qApp->processEvents();
        }
    } else {
        userLog->appendPlainText("There are too few source images to start calibration!");
    }
    return retVal;
}

/**
 * Returns the left camera object.
 * @return The 'CameraCalibration' object.
 */
scc::CameraCalibration* CalibrationHandler::getLeftCam() {
    return leftCam;
}

/**
 * Returns the right camera object.
 * @return The 'CameraCalibration' object.
 */
scc::CameraCalibration* CalibrationHandler::getRightCam() {
    return rightCam;
}

/**
 * Returns the stereo camera object.
 * @return The 'StereoCalibration' object.
 */
scc::StereoCalibration* CalibrationHandler::getStereoCam() {
    return stereoCam;
}

/**
 * Handels the calibration of the given camera object by processing each of its
 * source files and calculating the calibration data. It also gives feedback to
 * the user via the classes own 'userLog' element. During the process rotation
 * and distribution of the images are checked. If necessary more images are
 * added. In the end used images and calibration data are saved to the system.
 * @param cam The 'CameraCalibration' object to calibrate.
 * @param str String describing the 'CameraCalibration' object.
 */
void CalibrationHandler::handleCameraCalibration(scc::CameraCalibration *cam) {
    int imageStatus = 0;
    std::stringstream ss;
    ss << "\nCalibrating " << cam->getDescription() <<  " cam:\n";
    userLog->appendPlainText(QString::fromStdString(ss.str()));
    qApp->processEvents();
    while (imageStatus >= 0) {
        imageStatus = cam->processNextImage();
        if (imageStatus != -1) {
            replaceLastLineOfUserLog(cam->getStatus());
        }
    }

    // Check that there are enough usable images
    if (cam->getUsableSourceImageAmount() > 1) {

        unsigned int minAmountOfImages = 20;
        double percentageToRemove = 0.1;
        ss.str(std::string());
        ss.clear();
        ss << "The amount of images used for calibration will be reduced to "
           << minAmountOfImages << " by gradually removing "
           << 100 * percentageToRemove << " percent.";
        userLog->appendPlainText(QString::fromStdString(ss.str()));
        qApp->processEvents();

        // running initial calibration
        userLog->appendPlainText("Running initial calibration...");
        qApp->processEvents();
        double rms = cam->calibrate();
        unsigned int counter = 1;
        ss.str(std::string());
        ss.clear();
        ss << "RMS in run number " << counter << ": " << rms;
        counter++;
        userLog->appendPlainText(QString::fromStdString(ss.str()));
        qApp->processEvents();

        // removing bad rms images till 20 are left
        int removing = -1;
        while (removing != 1) {
            removing = cam->removeHighRms(minAmountOfImages, percentageToRemove);
            rms = cam->calibrate();
            ss.str(std::string());
            ss.clear();
            ss << "RMS in run number " << counter << ": " << rms;
            replaceLastLineOfUserLog(ss.str());
            counter++;
        }

        // computing rotation and translation for all usable images
        userLog->appendPlainText("Computing rotation and translation for all images ...");
        qApp->processEvents();
        cam->computeRotAndTransForAllImg();
        replaceLastLineOfUserLog("Computing rotation and translation for all images ... Done.");

        // computing rms for all usable images
        userLog->appendPlainText("Computing RMS for all images ...");
        qApp->processEvents();
        cam->computeReprojectionErrorForAllImg();
        replaceLastLineOfUserLog("Computing RMS for all images ... Done.");

        // check that there are more pictures than minimal needed
        if (cam->getUsableSourceImageAmount() > minAmountOfImages) {
            // remove images with bad rms from all usable images
            userLog->appendPlainText("Removing images with bad RMS from list of usable images ...");
            qApp->processEvents();
            float maxRms = 0.5;
            unsigned int amountRemoved = cam->removeHighRmsForAllImg(maxRms, minAmountOfImages);
            ss.str(std::string());
            ss.clear();
            ss << "Removed " << amountRemoved << " images with RMS higher than " << maxRms << " from list of usable images.";
            replaceLastLineOfUserLog(ss.str());

            // check for rotation in used images
            double minRotation = 60.0;
            ss.str(std::string());
            ss.clear();
            ss << "Checking used images for rotation over " << minRotation << " degrees ...";
            userLog->appendPlainText(QString::fromStdString(ss.str()));
            qApp->processEvents();
            if (!cam->checkUsedImagesForRotation(minRotation)) {
                ss.str(std::string());
                ss.clear();
                ss << "Used images have no rotation over " << minRotation << " degrees.";
                replaceLastLineOfUserLog(ss.str());
                int rotatedImagePos = cam->checkForRotatedImage(minRotation);
                if (rotatedImagePos != -1) {
                    cam->addImageFromUseableToUsed(rotatedImagePos);
                    userLog->appendPlainText("Added image with desired rotation.");
                    qApp->processEvents();
                    rms = cam->calibrate();
                    ss.str(std::string());
                    ss.clear();
                    ss << "New RMS is : " << rms;
                    userLog->appendPlainText(QString::fromStdString(ss.str()));
                    qApp->processEvents();
                } else {
                    userLog->appendPlainText("There is no image with desired rotation available.");
                    qApp->processEvents();
                }
            } else {
                ss.str(std::string());
                ss.clear();
                ss << "Used images have rotation over " << minRotation << " degrees.";
                replaceLastLineOfUserLog(ss.str());
            }

            // check for distribution
            ss.str(std::string());
            ss.clear();
            ss << "Computing calibration points ditribution ...";
            userLog->appendPlainText(QString::fromStdString(ss.str()));
            qApp->processEvents();
            if (!cam->computeImagePointDistribution()) {
                replaceLastLineOfUserLog("Computing calibration points ditribution ... Not ok.");
                qApp->processEvents();
                int found = 0;
                while (found != -1 && !cam->computeImagePointDistribution()) {
                    userLog->appendPlainText("Searching for images to get better distribution ...");
                    qApp->processEvents();
                    found = cam->checkForDistributedImage();
                    if (found != -1) {
                        cam->addImageFromUseableToUsed(found);
                        replaceLastLineOfUserLog("Added image with desired image point ditribution.");
                        qApp->processEvents();
                    } else {
                        replaceLastLineOfUserLog("Not enough images to fullfil complete distribution");
                        qApp->processEvents();
                    }
                }
                rms = cam->calibrate();
                ss.str(std::string());
                ss.clear();
                ss << "New RMS is : " << rms;
                replaceLastLineOfUserLog(ss.str());
                qApp->processEvents();
            } else {
                replaceLastLineOfUserLog("Computing calibration points ditribution ... Done and ok.");
                qApp->processEvents();
            }
        } else {
            userLog->appendPlainText("There are too few usable images for optimizing calibration!");
            qApp->processEvents();
        }


        // creating timestamp for saving
        time_t timeStamp;
        struct tm *timeInfo;
        char timeStr[80];
        time(&timeStamp);
        timeInfo = localtime(&timeStamp);
        strftime(timeStr, 80, "%Y-%m-%d_%H-%M-%S", timeInfo);

        // saving data
        userLog->appendPlainText("Saving calibration data...");
        qApp->processEvents();
        ss.str(std::string());
        ss.clear();
        ss << "calibration_" << cam->getDescription() << "_" << timeStr;
        cam->saveData(ss.str());
        replaceLastLineOfUserLog("Saving calibration data... Done.");
        qApp->processEvents();
    } else {
        userLog->appendPlainText("There are too few usable images for calibration!");
    }
}

/**
 * Returns a string representing the object and its attributes.
 * @return The string representing the object.
 */
std::string CalibrationHandler::print() {
    std::string retString = "";
    retString.append("CalibrationHandler Object\n");
    retString.append("=========================\n");
    retString.append("\nLeft camera:\n");
    retString.append(leftCam->print());
    retString.append("\nRight camera:\n");
    retString.append(rightCam->print());
    return retString;
}

/**
 * Converts the elements contained by the given QListWidget into strings and
 * returns them inside a vector.
 * @param listToConvert The 'QListWidget' object to cenvert.
 * @return A vector containing the converted strings.
 */
std::vector<std::string>
    CalibrationHandler::convertQListWidgetToVectorOfStrings(
                                                QListWidget *listToConvert) {
    std::vector<std::string> retVector;
    for (int i = 0; i < listToConvert->count(); i++) {
       retVector.push_back(listToConvert->item(i)->text().toUtf8().constData());
    }
    return retVector;
}

/**
 * Replaces the last line of the 'userLog' element which is a QPlainTextEdit
 * object with the given string. Afterwards the Qt main applikation is forced
 * to process its outstanding events to update its GUI / 'userLog'.
 * @param line The string to replace the last line with.
 */
void CalibrationHandler::replaceLastLineOfUserLog(std::string line) {
    QTextCursor storeCursorPos = userLog->textCursor();
    userLog->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    userLog->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    userLog->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
    userLog->textCursor().removeSelectedText();
    userLog->textCursor().deletePreviousChar();
    userLog->setTextCursor(storeCursorPos);
    userLog->appendPlainText(QString::fromStdString(line));
    qApp->processEvents();
}

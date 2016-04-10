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

#ifndef CALIBRATIONPREPARATION_H
#define CALIBRATIONPREPARATION_H

#include <QtWidgets>
#include <QDebug>

#include "calibrationhandler.h"
#include "calibrationevaluation.h"

class CalibrationPreparation : public QWidget {
    Q_OBJECT

public:
    explicit CalibrationPreparation(QTabWidget *parent);
    ~CalibrationPreparation();

signals:

public slots:

private slots:
    void runCalibrationSlot();

    // Collect input values
    void setLeftSourceSlot();
    void setRightSourceSlot();
    void setNumberOfSquaresHSlot(int number);
    void setNumberOfSquaresVSlot(int number);
    void setSizeOfSquaresSlot(int size);

private:
    // Parent widget
    QTabWidget *tabW;

    // Input vars and widgets
    int numberOfSquaresH;
    QSpinBox *numberOfSquaresSpinBoxH;
    int numberOfSquaresV;
    QSpinBox *numberOfSquaresSpinBoxV;

    int sizeOfSquares;
    QSpinBox *sizeOfSquaresSpinBox;

    QLineEdit *sourceLeftCameraLineEdit;
    QPushButton *sourceLeftCameraFileDialogButton;
    QListWidget *sourceLeftCameraPathListWidget;

    QLineEdit *sourceRightCameraLineEdit;
    QPushButton *sourceRightCameraFileDialogButton;
    QListWidget *sourceRightCameraPathListWidget;

    // Start calibration button
    QPushButton *calibrateButton;
    CalibrationHandler *calibrationHandler;

    // For user feedback
    QPlainTextEdit *logWindow;

    // Layout
    void setupLayout();
    void setPatternDimensionLayout(QWidget *widget);
    void setPatternSizeLayout(QWidget *widget);
    void addHLineToLayout(QFrame *frame);
    void addVLineToLayout(QFrame *frame);
    void setSourceLayout(QWidget *widget);
    void setUserLogLayout(QPlainTextEdit *textEdit);
    void connectSlots();

    // Check source files
    bool sourceIsUsable();

};

#endif // CALIBRATIONPREPARATION_H

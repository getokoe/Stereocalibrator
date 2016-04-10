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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QDebug>

#include "calibrationpreparation.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();


public slots:

private slots:
    // Menu slots.
    void openStereoCalibrationSlot();
    void openAboutSlot();

private:
    // Menu vars and actions
    QMenu *mainMenu;
    QAction *stereoCalibrationAction;
    QAction *exitAction;
    QMenu *aboutMenu;
    QAction *aboutAction;

    // Layout vars
    QTabWidget *tabWidget;

    void setupLayout();
    void createActions();
    void createMenu();
    void createStatusbar();
};

#endif // MAINWINDOW_H

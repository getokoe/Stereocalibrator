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

#include "mainwindow.h"

/**
 * Default constructor
 */
MainWindow::MainWindow() {
    setupLayout();
    createActions();
    createMenu();
    createStatusbar();
    //this->showMaximized();
}

/**
 * Sets up the main windows layout.
 */
void MainWindow::setupLayout() {
    qDebug() << "setupLayout():";

    QHBoxLayout *mainLayout = new QHBoxLayout;
    tabWidget = new QTabWidget;
    tabWidget->addTab(new CalibrationPreparation(tabWidget), tr("Calibration preparation"));
    mainLayout->addWidget(tabWidget);
    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

    setCentralWidget(window);
}

/**
 * Creates the actions for the menu and connects connects them to its specific
 * menu entry.
 */
void MainWindow::createActions() {
    qDebug() << "createActions():";
    stereoCalibrationAction = new QAction(tr("&Stereocalibration"), this);
    stereoCalibrationAction->setStatusTip(
                                       tr("Calibrate a stereo camera."));
    connect(stereoCalibrationAction, SIGNAL(triggered()), this,
            SLOT(openStereoCalibrationSlot()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setStatusTip(tr("Exit this programm!"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Info about this programm!"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(openAboutSlot()));
}

/**
 * Creates the menu with its entries for the main window.
 */
void MainWindow::createMenu() {
    qDebug() << "createMenu():";
    mainMenu = menuBar()->addMenu(tr("&Main"));
    mainMenu->addAction(stereoCalibrationAction);
    mainMenu->addSeparator();
    mainMenu->addAction(exitAction);

    menuBar()->addSeparator();

    aboutMenu = menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAction);
}

/**
 * Creates the status bar of the main window.
 */
void MainWindow::createStatusbar() {
    qDebug() << "createStatusbar():";
    statusBar();
}

/**
 * Destructor.
 */
MainWindow::~MainWindow() {
    qDebug() << "~MainWindow():";
}

/**
 * The slot called if the menu entry 'stereo calibration' was selected.
 */
void MainWindow::openStereoCalibrationSlot() {
    qDebug() << "openStereoCalibrationSlot():";
    setupLayout();
}

/**
 * The slot called if the menu entry 'about' was selected. It shows a message
 * box with information about the programm and its author.
 */
void MainWindow::openAboutSlot() {
    qDebug() << "openAboutSlot():";
    QMessageBox *aboutMessage = new QMessageBox;
    aboutMessage->about(this, tr("About StereoCalibrator"),
                           tr("This application was developed by <b>Tom "
                              "Koeppchen</b> (gtkoeppchen@googlemail.com) for "
                              "his bachelor thesis at the <b>HTW Berlin</b> "
                              "during winter 2015 / 2016"));
}

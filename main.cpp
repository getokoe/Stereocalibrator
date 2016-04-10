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

#include <QApplication>
#include <QDebug>

#include "./mainwindow.h"

/**
 * Programm for calibrating stereo camera systems.s
 */
int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    qDebug() << "app started...";

    MainWindow mainWindow;
    qDebug() << "mainWindow created...";
    mainWindow.show();
    qDebug() << "mainWindow shown...";

    return application.exec();
}

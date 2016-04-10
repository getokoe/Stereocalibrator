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

#include "calibrationpreparation.h"

/**
 * Constructur.
 * @param parent The widget being the parent of this object.
 */
CalibrationPreparation::CalibrationPreparation(QTabWidget *parent) :
    QWidget(parent) {
    tabW =  parent;
    qDebug() << "CalibrationPreparation(QWidget *parent):";
    setupLayout();
}

/**
 * Destructor.
 */
CalibrationPreparation::~CalibrationPreparation() {
    qDebug() << "~CalibrationPreparation():";
}

/**
 * Sets up the layout.
 */
void CalibrationPreparation::setupLayout() {
    qDebug() << "setupLayout():";

    // Central horizontal layout
    qDebug() << "... setting up main layout.";
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // chessboard pattern area horizontal layout
    QWidget *chessboardPatternAreaWidget = new QWidget;
    setPatternDimensionLayout(chessboardPatternAreaWidget);
    mainLayout->addWidget(chessboardPatternAreaWidget);

    // Size of squares area horizontal layout
    QWidget *sizeOfSquaresAreaWidget = new QWidget;
    setPatternSizeLayout(sizeOfSquaresAreaWidget);
    mainLayout->addWidget(sizeOfSquaresAreaWidget);

    // Horizontal seperator line
    QFrame* hLine = new QFrame();
    addHLineToLayout(hLine);
    mainLayout->addWidget(hLine);

    // Source area horizontal layout
    QWidget *sourceAreaWidget = new QWidget;
    setSourceLayout(sourceAreaWidget);
    mainLayout->addWidget(sourceAreaWidget);

    // Horizontal seperator line
    qDebug() << "... adding horizontal seperator.";
    QFrame* hLineTwo = new QFrame();
    addHLineToLayout(hLineTwo);
    mainLayout->addWidget(hLineTwo);

    // Calibrate button
    qDebug() << "... adding calibrate button.";
    calibrateButton = new QPushButton(tr("&Calibrate"));
    mainLayout->addWidget(calibrateButton);

    // Log window
    logWindow = new QPlainTextEdit;
    setUserLogLayout(logWindow);
    mainLayout->addWidget(logWindow);

    // Set central layout and widget
    setLayout(mainLayout);
    qDebug() << "... set central widget.";
    //setCentralWidget(window);

    connectSlots();
}

/**
 * Sets the layout for a given widget. The layout enables the user to provide
 * the dimensions of the calibration pattern for the calibration process.
 * @param widget The widget to set the layout for.
 */
void CalibrationPreparation::setPatternDimensionLayout(QWidget *widget) {
    qDebug() << "setPatternDimensionLayout(QWidget widget):";
    QHBoxLayout *chessboardPatternAreaLayout = new QHBoxLayout;

    // number of squares, horizontal layout
    // TODO: perhaps we can discover this value during processing...?
    qDebug() << "... setting up number of squares area elements.";
    QLabel *numberOfSquaresLabelH = new QLabel(
                tr("Select number of calibration pattern elements."));
    QLabel *horizont = new QLabel(tr("Horizontal:"));
    horizont->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    chessboardPatternAreaLayout->addWidget(numberOfSquaresLabelH);
    chessboardPatternAreaLayout->addWidget(horizont);
    numberOfSquaresSpinBoxH = new QSpinBox();
    numberOfSquaresSpinBoxH->setMinimum(1);
    numberOfSquaresSpinBoxH->setMaximum(100);
    numberOfSquaresSpinBoxH->setValue(9);
    numberOfSquaresH = numberOfSquaresSpinBoxH->value();
    chessboardPatternAreaLayout->addWidget(numberOfSquaresSpinBoxH);

    qDebug() << "... setting up number of squares area elements.";
    QLabel *numberOfSquaresLabelV = new QLabel(tr("Vertical:"));
    //numberOfSquaresLabelV->setLayoutDirection(Qt::RightToLeft);
    numberOfSquaresLabelV->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    chessboardPatternAreaLayout->addWidget(numberOfSquaresLabelV);
    numberOfSquaresSpinBoxV = new QSpinBox();
    numberOfSquaresSpinBoxV->setMinimum(1);
    numberOfSquaresSpinBoxV->setMaximum(100);
    numberOfSquaresSpinBoxV->setValue(7);
    numberOfSquaresV = numberOfSquaresSpinBoxV->value();
    chessboardPatternAreaLayout->addWidget(numberOfSquaresSpinBoxV);

    // Set number of squares area layout and widget
    qDebug() << "... adding type of source widget to main layout.";
    widget->setLayout(chessboardPatternAreaLayout);
}

/**
 * Sets the layout for a given widget. The layout enables the user to provide
 * the size of the calibration pattern elements for the calibration process.
 * @param widget The widget to set the layout for.
 */
void CalibrationPreparation::setPatternSizeLayout(QWidget *widget) {
    qDebug() << "setPatternSizeLayout(QWidget *widget):";
    QHBoxLayout *sizeOfSquaresAreaLayout = new QHBoxLayout;

    // Size of squares area elements
    qDebug() << "... setting up size of squares area elements.";
    QLabel *sizeOfSquaresLabel = new QLabel(
                tr("Set the size (mm) of the calibration pattern elements: "));
    sizeOfSquaresAreaLayout->addWidget(sizeOfSquaresLabel);
    sizeOfSquaresSpinBox = new QSpinBox();
    sizeOfSquaresSpinBox->setMinimum(1);
    sizeOfSquaresSpinBox->setMaximum(1000);
    sizeOfSquaresSpinBox->setValue(40);
    sizeOfSquares = sizeOfSquaresSpinBox->value();
    sizeOfSquaresAreaLayout->addWidget(sizeOfSquaresSpinBox);

    // Set way of source selection area layout and widget
    qDebug() << "... adding way of source widget to main layout.";
    widget->setLayout(sizeOfSquaresAreaLayout);
}

/**
 * Sets the layout for a given QFrame object. The layout will be a horizontal
 * sunken line.
 * @param frame The QFrame object to set the layout for.
 */
void CalibrationPreparation::addHLineToLayout(QFrame *frame) {
    qDebug() << "addHLineToLayout(QWidget *widget):";
    frame->setFrameShape(QFrame::HLine);
    frame->setFrameShadow(QFrame::Sunken);
}

/**
 * Sets the layout for a given QFrame object. The layout will be a vertical
 * sunken line.
 * @param frame The QFrame object to set the layout for.
 */
void CalibrationPreparation::addVLineToLayout(QFrame *frame) {
    qDebug() << "addVLineToLayout(QFrame *frame)";
    frame->setFrameShape(QFrame::VLine);
    frame->setFrameShadow(QFrame::Sunken);
}

/**
 * Sets the layout for a given widget. The layout enables the user to provide
 * the source files for the calibration process.
 * @param widget The widget to set the layout for.
 */
void CalibrationPreparation::setSourceLayout(QWidget *widget) {
    qDebug() << "setSourceLayout(QWidget *widget):";
    QHBoxLayout *sourceAreaLayout = new QHBoxLayout;

    // Left source vertical layout
    qDebug() << "... setting up left source area widget and layout.";
    QWidget *leftSource = new QWidget;
    QVBoxLayout *leftSourceLayout = new QVBoxLayout;

    // Left source label
    qDebug() << "... setting up left source area elements.";
    // Left source location widget with horizontal layout source line + button
    sourceLeftCameraFileDialogButton = new QPushButton(tr("&Left source"));
    // TODO: add clear button
    // TODO: show number of elemnts in list
    leftSourceLayout->addWidget(sourceLeftCameraFileDialogButton);
    // Left source preview
    sourceLeftCameraPathListWidget = new QListWidget;
    leftSourceLayout->addWidget(sourceLeftCameraPathListWidget);

    // Set left source layout and widget
    qDebug() << "... set left source widget.";
    leftSource->setLayout(leftSourceLayout);
    sourceAreaLayout->addWidget(leftSource);
    // Vertikal seperator line
    qDebug() << "... adding vertical seperator.";
    QFrame* vLine = new QFrame();
    addVLineToLayout(vLine);
    sourceAreaLayout->addWidget(vLine);

    // Right source vertical layout
    qDebug() << "... setting up right source area layout and widget.";
    QWidget *rightSource = new QWidget;
    QVBoxLayout *rightSourceLayout = new QVBoxLayout;
    sourceRightCameraFileDialogButton = new QPushButton(tr("&Right source"));
    // TODO: add clear button
    // TODO: show number of elemnts in list
    rightSourceLayout->addWidget(sourceRightCameraFileDialogButton);
    // Right source preview
    sourceRightCameraPathListWidget = new QListWidget;
    rightSourceLayout->addWidget(sourceRightCameraPathListWidget);

    // Set right source layout and widget
    qDebug() << "... set right source widget.";
    rightSource->setLayout(rightSourceLayout);
    sourceAreaLayout->addWidget(rightSource);

    // Set source area layout and widget
    qDebug() << "... set source widget.";
    widget->setLayout(sourceAreaLayout);
}

/**
 * Sets the layout for a given QPlainTextEdit to have a minimum size, specific
 * coloring and read/write-mode.
 * @param textEdit The QPlainTextEdit to set the layout for.
 */
void CalibrationPreparation::setUserLogLayout(QPlainTextEdit *textEdit) {
    qDebug() << "setUserLogLayout(QPlainTextEdit *textEdit):";
    textEdit->setReadOnly(true);
    textEdit->setMinimumHeight(50);
    textEdit->setMinimumWidth(1);
    QPalette palette;
    palette.setColor(QPalette::Base,Qt::black);
    palette.setColor(QPalette::Text,Qt::white);
    textEdit->setPalette(palette);
}

/**
 * Connects the GUI elements provided for user interaction with its specified
 * slots.
 */
void CalibrationPreparation::connectSlots() {
    qDebug() << "connectSlots():";
    connect(sourceLeftCameraFileDialogButton, SIGNAL(clicked()), this,
            SLOT(setLeftSourceSlot()));
    connect(sourceRightCameraFileDialogButton, SIGNAL(clicked()), this,
            SLOT(setRightSourceSlot()));
    qDebug() << "... connected file dialog slots.";
    connect(numberOfSquaresSpinBoxH, SIGNAL(valueChanged(int)), this,
            SLOT(setNumberOfSquaresHSlot(int)));
    connect(numberOfSquaresSpinBoxV, SIGNAL(valueChanged(int)), this,
            SLOT(setNumberOfSquaresVSlot(int)));
    connect(sizeOfSquaresSpinBox, SIGNAL(valueChanged(int)), this,
            SLOT(setSizeOfSquaresSlot(int)));
    qDebug() << "... connected chessboard pattern slots.";
    connect(calibrateButton, SIGNAL(clicked()), this,
            SLOT(runCalibrationSlot()));
    qDebug() << "... connected calibrate button.";
}

/**
 * Runs the calibration process by creating a calibrationhandler object,
 * disabling user input and calling the calibrationhandler object to handle
 * the calibration.
 */
void CalibrationPreparation::runCalibrationSlot() {
    qDebug() << "runCalibrationSlot:";
    if (sourceIsUsable() == true) {
        calibrationHandler = new CalibrationHandler(logWindow, sizeOfSquares,
                                            numberOfSquaresH, numberOfSquaresV,
                                            sourceLeftCameraPathListWidget,
                                            sourceRightCameraPathListWidget);
        qDebug() << "... created CalibrationHandler.";
        numberOfSquaresSpinBoxH->setEnabled(false);
        numberOfSquaresSpinBoxV->setEnabled(false);
        sizeOfSquaresSpinBox->setEnabled(false);
        sourceLeftCameraFileDialogButton->setEnabled(false);
        sourceRightCameraFileDialogButton->setEnabled(false);
        calibrateButton->setEnabled(false);
        qApp->processEvents();
        if (calibrationHandler->handleStereoCalibration()) {
            tabW->addTab(new CalibrationEvaluation(calibrationHandler->getLeftCam(), calibrationHandler->getRightCam(), calibrationHandler->getStereoCam()), "Calibration evaluation");
            tabW->setCurrentIndex(tabW->count() - 1);
        } else {
            numberOfSquaresSpinBoxH->setEnabled(true);
            numberOfSquaresSpinBoxV->setEnabled(true);
            sizeOfSquaresSpinBox->setEnabled(true);
            sourceLeftCameraFileDialogButton->setEnabled(true);
            sourceRightCameraFileDialogButton->setEnabled(true);
            calibrateButton->setEnabled(true);
        }
        // TODO: update calibration input paras?
        //this->setEnabled(true);
    }
}

/**
 * Opens a file dialog for choosing calibration source files. If the right
 * source files list already contains elements it sets the file filter to the
 * specified file type (it only checks for images / video; not for real MIME
 * TYPE).
 */
void CalibrationPreparation::setLeftSourceSlot() {
    qDebug() << "setLeftSourceSlot:";
    QString fileFilter = "";
    if (sourceRightCameraPathListWidget->count() == 0) {
        fileFilter = tr("Picture files (*.jpg *.jpeg *.JPG *.JPEG);"
                        ";Video files (*.mpeg *.mp4 *.avi)");
    } else {
        QMimeDatabase db;
        QMimeType type = db.mimeTypeForFile(
                    sourceRightCameraPathListWidget->item(0)->text());
        if (strstr(type.name().toLocal8Bit().constData(), "image") != NULL) {
            fileFilter = tr("Picture files (*.jpg *.jpeg *.JPG *.JPEG)");
        } else if (strstr(type.name().toLocal8Bit().constData(),
                          "video") != NULL) {
            fileFilter = tr("Video files (*.mpeg *.mp4 *.avi)");
        } else {
            fileFilter = tr("");
        }
    }
    QStringList tempList = QFileDialog::getOpenFileNames(this,
                                        tr("Choose files for left camera..."),
                                        "/home/gtk/Calibration", fileFilter);
    qDebug() << "... tempList: " << tempList;
    sourceLeftCameraPathListWidget->addItems(tempList);
}

/**
 * Opens a file dialog for choosing calibration source files. If the left
 * source files list already contains elements it sets the file filter to the
 * specified file type (it only checks for images / video; not for real MIME
 * TYPE).
 */
void CalibrationPreparation::setRightSourceSlot() {
    qDebug() << "setRightSourceSlot:";
    QString fileFilter = "";
    if (sourceLeftCameraPathListWidget->count() == 0) {
        fileFilter = tr("Picture files (*.jpg *.jpeg *.JPG *.JPEG);"
                        ";Video files (*.mpeg *.mp4 *.avi)");
    } else {
        QMimeDatabase db;
        QMimeType type = db.mimeTypeForFile(
                    sourceLeftCameraPathListWidget->item(0)->text());
        if (strstr(type.name().toLocal8Bit().constData(), "image") != NULL) {
            fileFilter = tr("Picture files (*.jpg *.jpeg *.JPG *.JPEG)");
        } else if (strstr(type.name().toLocal8Bit().constData(),
                          "video") != NULL) {
            fileFilter = tr("Video files (*.mpeg *.mp4 *.avi)");
        } else {
            fileFilter = tr("");
        }
    }
    QStringList tempList = QFileDialog::getOpenFileNames(this,
                                        tr("Choose files for right camera..."),
                                        "/home/gtk/Calibration", fileFilter);
    qDebug() << "... tempList: " << tempList;
    sourceRightCameraPathListWidget->addItems(tempList);
}

/**
 * Sets the number of horizontal calibration patern elements.
 * @param number Integeger value representing the amount.
 */
void CalibrationPreparation::setNumberOfSquaresHSlot(int number) {
    qDebug() << "setNumberOfSquaresHSlot(int number):" << number;
    numberOfSquaresH = number;
    qDebug() << "... numberOfSquaresH: " << numberOfSquaresH;
}

/**
 * Sets the number of vertical calibration pattern elements.
 * @param number Integer value representing the amount.
 */
void CalibrationPreparation::setNumberOfSquaresVSlot(int number) {
    qDebug() << "setNumberOfSquaresVSlot(int number):" << number;
    numberOfSquaresV = number;
    qDebug() << "... numberOfSquaresV: " << numberOfSquaresV;
}

/**
 * Sets the size of the calibration patern elements.
 * @param size Integer value representing the size.
 */
void CalibrationPreparation::setSizeOfSquaresSlot(int size) {
    qDebug() << "setSizeOfSquaresSlot(int size):" << size;
    sizeOfSquares = size;
    qDebug() << "... sizeOfSquares: " << sizeOfSquares;
}

/**
 * Checks whether both lists of source file are not empty and have the same
 * number of elements.
 * @return True if both lists have the same length and are not empty, otherwise
 *          False.
 */
bool CalibrationPreparation::sourceIsUsable() {
    qDebug() << "sourceIsUsable:";
    bool retVal = true;
    QString errorMessage = "";
    if (sourceLeftCameraPathListWidget->count() == 0) {
        retVal = false;
        errorMessage = tr("No source files selected for left camera.");
        qDebug() << "... no source files for left camera.";
    } else if (sourceRightCameraPathListWidget->count() == 0) {
        retVal = false;
        errorMessage = tr("No source files selected for right camera.");
        qDebug() << "... no source files for right camera.";
    } else if (sourceLeftCameraPathListWidget->count() !=
               sourceRightCameraPathListWidget->count()) {
        retVal = false;
        errorMessage = tr("There has to be the same amount of source files for"
                          "left and right camera.");
        qDebug() << "... sources dont have same size.";
    }
    if (retVal == false){
        QMessageBox *dialog = new QMessageBox(this);
        dialog->setText(errorMessage);
        dialog->setIcon(QMessageBox::Critical);
        dialog->exec();
    }
    return retVal;
}

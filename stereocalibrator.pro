#-------------------------------------------------
#
# Project created by QtCreator 2016-01-01T11:23:45
#
#-------------------------------------------------

CONFIG   += qt

QT       += widgets

TARGET = Stereocalibrator

QMAKE_CFLAGS += -pedantic -Wall -Wextra -Werror
QMAKE_CFLAGS += `pkg-config --cflags opencv`

LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videostab -ltbb -lGL -lGLU -lrt -lpthread -lm -ldl

LIBS += -L/usr/local/lib -lcnpy
LIBS += -L/usr/local/lib -lstereocamcalib

SOURCES += main.cpp \
    mainwindow.cpp \
    calibrationhandler.cpp \
    calibrationpreparation.cpp \
    calibrationevaluation.cpp \
    cameracalibrationevaluation.cpp \
    stereocalibrationevaluation.cpp

HEADERS += \
    mainwindow.h \
    calibrationhandler.h \
    calibrationpreparation.h \
    calibrationevaluation.h \
    cameracalibrationevaluation.h \
    stereocalibrationevaluation.h

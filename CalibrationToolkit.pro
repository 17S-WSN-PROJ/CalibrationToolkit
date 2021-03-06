#-------------------------------------------------
#
# Project created by QtCreator 2017-03-03T19:55:02
#
#-------------------------------------------------

QT       += widgets opengl xml serialport charts

TARGET = CalibrationToolkit
TEMPLATE = lib

DEFINES += CALIBRATIONTOOLKIT_LIBRARY

SOURCES += \
    CameraHub.cpp \
    ImageView.cpp \
    ImuHub.cpp \
    ImuDecoder.cpp \
    imuserialportreader.cpp \
    ImuMessageView.cpp \
    ImuRos.cpp \
    CameraCalibration.cpp \
    cameracalibrationwidget.cpp \
    ImuCalibration.cpp \
    imucalibrationwidget.cpp \
    ImuLogger.cpp \
    ImageLogger.cpp \
    ImuHubRec.cpp \
    ImuHubSim.cpp \
    ImuBodyVis.cpp \
    ImuDeviceIndicator.cpp \
    VideoReplay.cpp

HEADERS += \
    CameraHub.h \
    ImageView.h \
    ImuHub.h \
    ImuDecoder.h \
    imuserialportreader.h \
    ImuMessageView.h \
    ImuRos.h \
    CameraCalibration.h \
    cameracalibrationwidget.h \
    ImuCalibration.h \
    imucalibrationwidget.h \
    ImuLogger.h \
    ImageLogger.h \
    ImuHubRec.h \
    ImuHubSim.h \
    ImuBodyVis.h \
    ImuDeviceIndicator.h \
    VideoReplay.h


INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib \
    -lopencv_core -lopencv_highgui -lopencv_calib3d -lopencv_imgproc -lopencv_videoio


include($$(HOME)/SDK/RobotSDK_4.0/Kernel/RobotSDK.pri)

#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T20:17:56
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Maska
TEMPLATE = app

CONFIG += static

SOURCES += main.cpp\
        maska.cpp \
    map.cpp \
    car.cpp \
    constants.cpp \
    mapviewer.cpp

HEADERS  += maska.h \
    map.h \
    constants.h \
    car.h \
    mapviewer.h

FORMS    += \
    maska.ui

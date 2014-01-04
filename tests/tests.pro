#-------------------------------------------------
#
# Project created by QtCreator 2014-01-01T19:58:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ../include


SOURCES += main.cpp \
    Temperature.cpp \
    VolumicMass.cpp \
    MolecularMass.cpp

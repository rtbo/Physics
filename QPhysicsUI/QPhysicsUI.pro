
QT       += widgets

TARGET = QPhysicsUI
TEMPLATE = lib

DEFINES += QPHYSICS_LIBRARY


QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/../include


include(src.pri)


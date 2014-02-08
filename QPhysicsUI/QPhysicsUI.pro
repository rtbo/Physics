
QT       += widgets

TARGET = QPhysicsUI
TEMPLATE = lib

DEFINES += QPHYSICSUI_LIBRARY


QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/../Physics/include


include(src.pri)


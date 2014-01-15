
QT = core

TARGET = QPhysics
TEMPLATE = lib

CONFIG += static

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += include $$PWD/../include

HEADERS = include/QPhysics.hpp
SOURCES = QPhysics.cpp

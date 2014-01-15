
CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(QPhysicsDesigner)
TEMPLATE    = lib




QMAKE_CXXFLAGS += -std=c++11

DEFINES +=  QPHYSICS_NODLL


include(../QPhysicsUI/src.pri)


for( includeP, INCLUDEPATH) {
    QPHYSICS_DESIGNER_INCLUDEPATH += $$PWD/../QPhysicsUI/$${includeP}
}

for( header, HEADERS) {
    QPHYSICS_DESIGNER_HEADERS += $$PWD/../QPhysicsUI/$${header}
}

for( source, SOURCES ) {
    QPHYSICS_DESIGNER_SOURCES += $$PWD/../QPhysicsUI/$${source}
}


INCLUDEPATH = $${QPHYSICS_DESIGNER_INCLUDEPATH}

HEADERS = $${QPHYSICS_DESIGNER_HEADERS}

SOURCES = $${QPHYSICS_DESIGNER_SOURCES}




INCLUDEPATH += $$PWD/../include
HEADERS += QPhysicsDesignerPlugin.hpp
SOURCES += QPhysicsDesignerPlugin.cpp



RESOURCES   = icons.qrc


greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

CONFIG(debug, debug|release) {
    CURBUILD = debug
} else {
    CURBUILD = release
}

# to test the designer plugin, we provide an environment switch that
# trigger a copy to the qt dir of the necessary files after link:
# QtDir/plugins/designer/QPhysicsDesigner.dll
_DO_COPY = $$(COPY_TO_QT_BIN)

!isEmpty( _DO_COPY ) {
    TARGET_FILE = $$shell_path($$OUT_PWD/$$CURBUILD/$${TARGET}.dll)
    INSTALLED_FILE = $$shell_path($$[QT_INSTALL_PLUGINS]\designer)

    QMAKE_POST_LINK += $$QMAKE_COPY $$TARGET_FILE $$INSTALLED_FILE
}


target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target



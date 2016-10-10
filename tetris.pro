TEMPLATE = app debug
TARGET = tetris

QT += widgets core
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += inc/
SOURCES += src/*
HEADERS += inc/*
RESOURCES += tetris.qrc

OBJECTS_DIR = obj/
MOC_DIR = obj/
QMAKE_CLEAN += obj/*.o obj/moc_*

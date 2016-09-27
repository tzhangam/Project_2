TEMPLATE = app
TARGET = tetris

QT += widgets core
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ./inc/
SOURCES += src/main.cpp \
           src/Block.cpp \
           src/RenderArea.cpp \
           src/Panel.cpp \
           src/Gameboard.cpp\
           src/Window.cpp
HEADERS += inc/Block.h \
           inc/Gameboard.h \
           inc/RenderArea.h \
           inc/Panel.h \
           inc/Window.h \
           inc/misc.h
QMAKE_CLEAN += *.o moc_*

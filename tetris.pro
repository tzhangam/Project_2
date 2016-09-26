TEMPLATE = app
TARGET = tetris

QT += widgets
CONFIG += console
INCLUDEPATH += ./inc/
SOURCES += src/main.cpp \
           src/Block.cpp \
           src/RenderArea.cpp \
           src/Gameboard.cpp\
           src/Window.cpp
HEADERS += inc/Block.h \
           inc/Gameboard.h \
           inc/RenderArea.h \
           inc/Window.h \
           inc/misc.h
QMAKE_CLEAN += *.o moc_*
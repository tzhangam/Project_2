TEMPLATE = app
TARGET = tetris

QT += widgets
CONFIG += console
INCLUDEPATH += ./inc/
SOURCES += src/main.cpp \
           src/Block.cpp \
           src/RenderArea.cpp \
           src/Window.cpp
HEADERS += inc/Block.h \
           inc/RenderArea.h \
           inc/Window.h
QMAKE_CLEAN += *.o moc_*
QT += widgets opengl
CONFIG += c++17

win32: LIBS += -lopengl32
win32-msvc: QMAKE_LFLAGS -= /DEBUG
win32-msvc: QMAKE_LFLAGS += /PDB:NONE

SOURCES += \
    main.cpp \
    myglwidget.cpp \
    startcaverncode.cpp

HEADERS += \
    myglwidget.h \
    startcaverncode.h

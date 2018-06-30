QT += widgets

CONFIG += c++14
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src\main.cpp \
    src\source.cpp \
    src\request.cpp \
    src\buffer.cpp \
    src\counter.cpp \
    src\consumer.cpp \
    src\constants.cpp \
    src\mainwindow.cpp \
    src\system.cpp \
    src\stepbystepwindow.cpp \
    src\resultswindow.cpp

HEADERS += \
    include\constants.h \
    include\source.h \
    include\request.h \
    include\buffer.h \
    include\counter.h \
    include\consumer.h \
    include\device.h \
    include\mainwindow.h \
    include\system.h \
    include\stepbystepwindow.h \
    include\resultswindow.h

FORMS += \
    gui\mainwindow.ui \
    gui\stepbystepwindow.ui \
    gui\resultswindow.ui

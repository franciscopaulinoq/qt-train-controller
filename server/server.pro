QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++17

SOURCES += main.cpp \
    controllertcpserver.cpp \
    serverwindow.cpp \
    trem.cpp

HEADERS  += \
    controllertcpserver.h \
    serverwindow.h \
    trem.h

FORMS    += \
    serverwindow.ui

TARGET = server
TEMPLATE = app

LIBS += -pthread

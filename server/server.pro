QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++17

SOURCES += main.cpp\
    serverwindow.cpp \
    trem.cpp

HEADERS  += \
    serverwindow.h \
    trem.h

FORMS    += \
    serverwindow.ui

TARGET = server
TEMPLATE = app

LIBS += -pthread
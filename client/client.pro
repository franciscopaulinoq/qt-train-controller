QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    clientwindow.cpp

HEADERS += \
    clientwindow.h

FORMS += \
    clientwindow.ui

TARGET = client
TEMPLATE = app

LIBS += -pthread
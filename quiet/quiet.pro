#-------------------------------------------------
#
# Project created by QtCreator 2022-03-24T10:26:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quiet
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    view/centralwidget.cpp \
    view/imagewidget.cpp \
    view/imagepanel.cpp \
    model/directorymanager.cpp \
    object/fsentry.cpp \
    model/imagemanager.cpp \
    object/image.cpp \
    model/loadimagetask.cpp \
    model/actionmanager.cpp \
    core.cpp \
    view/contextmenu.cpp \
    view/contextmenuitem.cpp

HEADERS  += \
    mainwindow.h \
    view/centralwidget.h \
    view/imagewidget.h \
    view/imagepanel.h \
    model/directorymanager.h \
    object/fsentry.h \
    model/imagemanager.h \
    object/image.h \
    model/loadimagetask.h \
    model/actionmanager.h \
    core.h \
    view/contextmenu.h \
    view/contextmenuitem.h

FORMS += \
    view/contextmenu.ui



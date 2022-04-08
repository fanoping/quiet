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
    view/contextmenu.cpp \
    view/contextmenuitem.cpp \
    view/gallarypanel.cpp \
    object/node.cpp

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
    view/contextmenu.h \
    view/contextmenuitem.h \
    util/constants.h \
    view/gallarypanel.h \
    object/node.h

FORMS += \
    view/contextmenu.ui



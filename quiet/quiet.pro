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
    model/imagemanager.cpp \
    object/image.cpp \
    model/actionmanager.cpp \
    view/gallarypanel.cpp \
    object/node.cpp \
    view/gallaryitem.cpp \
    util/themepalette.cpp \
    settings.cpp \
    core/core.cpp

HEADERS  += \
    mainwindow.h \
    view/centralwidget.h \
    view/imagewidget.h \
    view/imagepanel.h \
    model/directorymanager.h \
    model/imagemanager.h \
    object/image.h \
    model/actionmanager.h \
    util/constants.h \
    view/gallarypanel.h \
    object/node.h \
    util/utils.h \
    view/gallaryitem.h \
    util/themepalette.h \
    settings.h \
    core/core.h

FORMS +=



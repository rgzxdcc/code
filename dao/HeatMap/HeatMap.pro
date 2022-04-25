#-------------------------------------------------
#
# Project created by QtCreator 2022-03-18T14:56:44
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HeatMap
TEMPLATE = app

include(../osgoe.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  heatmap \
                heatmap/colorschemes

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    cheatmap.cpp \
    heatmap/lodepng.cpp \
    heatmap/heatmap.c \
    heatmap/colorschemes/Blues.c \
    heatmap/colorschemes/BrBG.c \
    heatmap/colorschemes/BuGn.c \
    heatmap/colorschemes/BuPu.c \
    heatmap/colorschemes/GnBu.c \
    heatmap/colorschemes/gray.c \
    heatmap/colorschemes/Greens.c \
    heatmap/colorschemes/Greys.c \
    heatmap/colorschemes/Oranges.c \
    heatmap/colorschemes/OrRd.c \
    heatmap/colorschemes/PiYG.c \
    heatmap/colorschemes/PRGn.c \
    heatmap/colorschemes/PuBu.c \
    heatmap/colorschemes/PuBuGn.c \
    heatmap/colorschemes/PuOr.c \
    heatmap/colorschemes/PuRd.c \
    heatmap/colorschemes/Purples.c \
    heatmap/colorschemes/RdBu.c \
    heatmap/colorschemes/RdGy.c \
    heatmap/colorschemes/RdPu.c \
    heatmap/colorschemes/RdYlBu.c \
    heatmap/colorschemes/RdYlGn.c \
    heatmap/colorschemes/Reds.c \
    heatmap/colorschemes/Spectral.c \
    heatmap/colorschemes/YlGn.c \
    heatmap/colorschemes/YlGnBu.c \
    heatmap/colorschemes/YlOrBr.c \
    heatmap/colorschemes/YlOrRd.c \
    heatmap/GxGradientPalette.cpp

HEADERS += \
        mainwindow.h \
    cheatmap.h \
    heatmap/heatmap.h \
    heatmap/lodepng.h \
    heatmap/colorschemes/Blues.h \
    heatmap/colorschemes/BrBG.h \
    heatmap/colorschemes/BuGn.h \
    heatmap/colorschemes/BuPu.h \
    heatmap/colorschemes/GnBu.h \
    heatmap/colorschemes/gray.h \
    heatmap/colorschemes/Greens.h \
    heatmap/colorschemes/Greys.h \
    heatmap/colorschemes/Oranges.h \
    heatmap/colorschemes/OrRd.h \
    heatmap/colorschemes/PiYG.h \
    heatmap/colorschemes/PRGn.h \
    heatmap/colorschemes/PuBu.h \
    heatmap/colorschemes/PuBuGn.h \
    heatmap/colorschemes/PuOr.h \
    heatmap/colorschemes/PuRd.h \
    heatmap/colorschemes/Purples.h \
    heatmap/colorschemes/RdBu.h \
    heatmap/colorschemes/RdGy.h \
    heatmap/colorschemes/RdPu.h \
    heatmap/colorschemes/RdYlBu.h \
    heatmap/colorschemes/RdYlGn.h \
    heatmap/colorschemes/Reds.h \
    heatmap/colorschemes/Spectral.h \
    heatmap/colorschemes/YlGn.h \
    heatmap/colorschemes/YlGnBu.h \
    heatmap/colorschemes/YlOrBr.h \
    heatmap/colorschemes/YlOrRd.h \
    heatmap/GxGradientPalette.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    heatmap/colorschemes/colorbrewer.go \
    heatmap/colorschemes/colorscheme.go \
    heatmap/colorschemes/gradientgen.go

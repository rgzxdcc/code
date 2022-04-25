#-------------------------------------------------
#
# Project created by QtCreator 2022-01-11T12:07:31
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../osgoe.pri)

TARGET = DccTestCt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  heatmap/3rdParty \
                heatmap/3rdParty/colorschemes \
                heatmap/src

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    CBottomPlusWgt.cpp \
    heatmap/3rdParty/colorschemes/Blues.c \
    heatmap/3rdParty/colorschemes/BrBG.c \
    heatmap/3rdParty/colorschemes/BuGn.c \
    heatmap/3rdParty/colorschemes/BuPu.c \
    heatmap/3rdParty/colorschemes/GnBu.c \
    heatmap/3rdParty/colorschemes/gray.c \
    heatmap/3rdParty/colorschemes/Greens.c \
    heatmap/3rdParty/colorschemes/Greys.c \
    heatmap/3rdParty/colorschemes/Oranges.c \
    heatmap/3rdParty/colorschemes/OrRd.c \
    heatmap/3rdParty/colorschemes/PiYG.c \
    heatmap/3rdParty/colorschemes/PRGn.c \
    heatmap/3rdParty/colorschemes/PuBu.c \
    heatmap/3rdParty/colorschemes/PuBuGn.c \
    heatmap/3rdParty/colorschemes/PuOr.c \
    heatmap/3rdParty/colorschemes/PuRd.c \
    heatmap/3rdParty/colorschemes/Purples.c \
    heatmap/3rdParty/colorschemes/RdBu.c \
    heatmap/3rdParty/colorschemes/RdGy.c \
    heatmap/3rdParty/colorschemes/RdPu.c \
    heatmap/3rdParty/colorschemes/RdYlBu.c \
    heatmap/3rdParty/colorschemes/RdYlGn.c \
    heatmap/3rdParty/colorschemes/Reds.c \
    heatmap/3rdParty/colorschemes/Spectral.c \
    heatmap/3rdParty/colorschemes/YlGn.c \
    heatmap/3rdParty/colorschemes/YlGnBu.c \
    heatmap/3rdParty/colorschemes/YlOrBr.c \
    heatmap/3rdParty/colorschemes/YlOrRd.c \
    heatmap/3rdParty/lodepng.cpp \
    heatmap/3rdParty/heatmap.c \
    heatmap/src/GxAnnotationNode.cpp \
    heatmap/src/GxHeatMapNode.cpp \
    heatmap/src/GxImageOverlay.cpp

HEADERS += \
        mainwindow.h \
    CBottomPlusWgt.h \
    heatmap/3rdParty/colorschemes/Blues.h \
    heatmap/3rdParty/colorschemes/BrBG.h \
    heatmap/3rdParty/colorschemes/BuGn.h \
    heatmap/3rdParty/colorschemes/BuPu.h \
    heatmap/3rdParty/colorschemes/GnBu.h \
    heatmap/3rdParty/colorschemes/gray.h \
    heatmap/3rdParty/colorschemes/Greens.h \
    heatmap/3rdParty/colorschemes/Greys.h \
    heatmap/3rdParty/colorschemes/Oranges.h \
    heatmap/3rdParty/colorschemes/OrRd.h \
    heatmap/3rdParty/colorschemes/PiYG.h \
    heatmap/3rdParty/colorschemes/PRGn.h \
    heatmap/3rdParty/colorschemes/PuBu.h \
    heatmap/3rdParty/colorschemes/PuBuGn.h \
    heatmap/3rdParty/colorschemes/PuOr.h \
    heatmap/3rdParty/colorschemes/PuRd.h \
    heatmap/3rdParty/colorschemes/Purples.h \
    heatmap/3rdParty/colorschemes/RdBu.h \
    heatmap/3rdParty/colorschemes/RdGy.h \
    heatmap/3rdParty/colorschemes/RdPu.h \
    heatmap/3rdParty/colorschemes/RdYlBu.h \
    heatmap/3rdParty/colorschemes/RdYlGn.h \
    heatmap/3rdParty/colorschemes/Reds.h \
    heatmap/3rdParty/colorschemes/Spectral.h \
    heatmap/3rdParty/colorschemes/YlGn.h \
    heatmap/3rdParty/colorschemes/YlGnBu.h \
    heatmap/3rdParty/colorschemes/YlOrBr.h \
    heatmap/3rdParty/colorschemes/YlOrRd.h \
    heatmap/3rdParty/heatmap.h \
    heatmap/3rdParty/lodepng.h \
    heatmap/src/GxAnnotationNode.h \
    heatmap/src/GxHeatMapNode.h \
    heatmap/src/GxImageOverlay.h

FORMS += \
        mainwindow.ui \
    CBottomPlusWgt.ui

DISTFILES += \
    heatmap/3rdParty/colorschemes/colorbrewer.go \
    heatmap/3rdParty/colorschemes/colorscheme.go \
    heatmap/3rdParty/colorschemes/gradientgen.go


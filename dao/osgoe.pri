#-------------------------------------------------
#
# Project created by QtCreator 2022-01-11T12:07:31
#
#-------------------------------------------------

#define 3d environment
OEENV = E:/dcc/resource/FxGIS_340

#osg
INCLUDEPATH += $${OEENV}/osg/include

CONFIG(release, debug|release){
LIBS += -L$${OEENV}/osg/lib -lOpenThreads -losg -losgDB -losgViewer -losgGA -losgQt
}
else{
LIBS += -L$${OEENV}/osg/lib -lOpenThreadsd -losgd -losgDBd -losgViewerd -losgGAd -losgQtd
}


#osgearth
INCLUDEPATH += $${OEENV}/osgearth/include

CONFIG(release, debug|release){
LIBS += -L$${OEENV}/osgearth/lib -losgEarth -losgEarthUtil -losgEarthFeatures -losgEarthAnnotation -losgEarthSymbology
}
else{
LIBS += -L$${OEENV}/osgearth/lib -losgEarthd -losgEarthUtild -losgEarthFeaturesd -losgEarthAnnotationd -losgEarthSymbologyd
}

#osgwgt
INCLUDEPATH += $$PWD
HEADERS += $$PWD/osgwgt.h
SOURCES += $$PWD/osgwgt.cpp

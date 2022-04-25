#include "mainwindow.h"
#include <QApplication>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgearth/MapNode>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();

    std::string earthPath = "E:/dcc/test/test.earth";
    osg::Node *node = osgDB::readNodeFile(earthPath);
    osgViewer::Viewer viewer;


    if (node)
    {
        osgEarth::MapNode *mapNode = osgEarth::MapNode::findMapNode(node);
        if (mapNode)
        {
            viewer.setSceneData(node);
        }

    }

    return viewer.run();
}

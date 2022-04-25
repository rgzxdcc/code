#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "osgwgt.h"

#include <osgDB/ReadFile>
#include <osgearth/MapNode>
#include <osg/ImageStream>
#include <osgGA/CameraManipulator>
#include <osgEarthAnnotation/ImageOverlay>

#include <QMessageBox>

#include "cheatmap.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    // create osgwgt
    OsgWgt *ow = new OsgWgt;
    setCentralWidget(ow);

    std::string earthPath = "E:/dcc/test/test.earth";
    osg::Node *node = osgDB::readNodeFile(earthPath);
    if (!node)
        return;

    osgEarth::MapNode *mapNode = osgEarth::MapNode::findMapNode(node);
    if (!mapNode)
        return;

    // 设置场景
    ow->getRoot()->addChild(node);

    // 创建贴地图
    osgEarth::Annotation::ImageOverlay *io = new  osgEarth::Annotation::ImageOverlay(mapNode);
    io->setCorners(osg::Vec2d(70.0, -20.0), osg::Vec2d(120.0, -20.0), osg::Vec2d(70.0, 30.0), osg::Vec2d(120.0, 30.0));
    osg::Image *image = osgDB::readImageFile("D:/testdata/Moon_1024x512.jpg");

    // 组织数据
    CHeatMap *hp = new CHeatMap(mapNode);
    QList<StHTPoint> listdata;
    for (double lng = 70.0; lng < 121.0; lng += 10.0)
    {
        for (double lat = -20; lat < 31.0; lat += 10.0)
        {
            StHTPoint sp(lng, lat, (qrand() % 10) / 10.0 + 0.5);
            listdata.append(sp);
        }
    }

    hp->setPoints(listdata);
    image = hp->getImage();

    if (!image)
    {
        QMessageBox::warning(nullptr, "warning", "sdfffff");
    }
    else
    {
        osg::ImageStream* is = dynamic_cast<osg::ImageStream*>(image);
        if (is)
        {
            is->play();
        }
    }
    io->setImage(image);
    io->setDraped(true);
//            io->setAlpha(0.5);
    ow->getRoot()->addChild(io);


    // 居中
    ow->getViewer()->getCameraManipulator()->home(5.0);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>

#include <osgDB/ReadFile>
#include <osgEarth/MapNode>
#include <osgGA/CameraManipulator>

#include "osgwgt.h"
#include "situationscene.h"
#include "controlwgt.h"

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

    // create scene
    _ss = new SituationScene(ow->getRoot());

    // create controlwgt
    controlwgt *cw = new controlwgt(_ss);
    QDockWidget *dock = new QDockWidget;
    dock->setWidget(cw);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    // 归心
    //ow->getViewer()->getCameraManipulator()->setHomePosition();
    ow->getViewer()->getCameraManipulator()->home(2.0);
}

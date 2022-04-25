#include "osgwgt.h"

#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>


OsgWgt::OsgWgt()
    :osgQt::GLWidget(QGLFormat(QGL::SampleBuffers))
{
    InitOsg();

    // frame opengl
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->start();
}

void OsgWgt::InitOsg()
{
    // create viewer
    _rpViewer = new osgViewer::Viewer;
    _rpViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);

    // create traits
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    osgQt::GraphicsWindowQt::WindowData *winData = new osgQt::GraphicsWindowQt::WindowData(this);
    traits->x = 0;
    traits->y = 0;
    traits->width = width();
    traits->height = height();
    traits->inheritedWindowData = winData;
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
    traits->setInheritedWindowPixelFormat = true;

    // create gc
    osg::GraphicsContext *gc = new osgQt::GraphicsWindowQt(traits);

    // create camera
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(gc);
    camera->setViewport(new osg::Viewport(0, 0, width(), height()));
    camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
    camera->setProjectionMatrixAsPerspective(30.0f, double(width()) / double(height()), 1.0f, 1000.0f);
    _rpViewer->setCamera(camera);

    // set manipulator
    _rpViewer->setCameraManipulator(new osgGA::TrackballManipulator);
    _rpViewer->addEventHandler(new osgViewer::StatsHandler);
    _rpViewer->addEventHandler(new osgGA::StateSetManipulator(camera->getOrCreateStateSet()));

    // create scene
    _rpRoot = new osg::Group;
    _rpViewer->setSceneData(_rpRoot);
}

void OsgWgt::paintEvent(QPaintEvent *e)
{
    if (_rpViewer.valid())
    {
        _rpViewer->frame();
    }

    osgQt::GLWidget::paintEvent(e);
}

void OsgWgt::resizeEvent(QResizeEvent *event)
{
    if (_rpViewer.valid())
    {
        _rpViewer->getCamera()->setViewport(new osg::Viewport(0, 0, width(), height()));
        _rpViewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, double(width()) / double(height()), 1.0f, 1000.0f);
    }
}

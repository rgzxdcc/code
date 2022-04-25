#ifndef OSG_WGT_H
#define OSG_WGT_H

#include <QTimer>
#include <QPaintEvent>

#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>


// osgqt窗口
class OsgWgt : public osgQt::GLWidget
{
public:
    OsgWgt();

    // 初始化osg
    void InitOsg();


    // 获取视景
    osgViewer::Viewer * getViewer() { return _rpViewer.get(); }

    // 获取根节点
    osg::Group *getRoot() { return _rpRoot.get(); }

protected:
    void paintEvent(QPaintEvent *e) override;

    void resizeEvent(QResizeEvent *event) override;
private:

    // 视景器
    osg::ref_ptr<osgViewer::Viewer> _rpViewer;

    // 根节点
    osg::ref_ptr<osg::Group>        _rpRoot;

    // 定时器
    QTimer *                        _timer;
};


#endif // OSG_WGT_H

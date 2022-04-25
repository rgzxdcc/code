#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SchemeDef.h"
#include <QDomElement>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

#include "CBottomPlusWgt.h"

#include <QMenu>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    menuBar()->addAction("输出态势资源", this, SLOT(changeResources()));
    std::string begin, end;
    int i = 0;
    std::string test = begin;

    statusBar()->hide();

    // 测试按钮窗口
    QMenu *menu = new QMenu(this);
    QMenu * secMenu = menu->addMenu("民兵部署");
    QMenu * thdMenu = secMenu->addMenu("应急排");
    thdMenu->addAction("修改民兵部署");
    thdMenu->addAction("删除民兵部署");
    thdMenu = secMenu->addMenu(QString("wsb"));
    thdMenu->addAction("修改民兵部署");
    thdMenu->addAction("删除民兵部署");
    secMenu->addAction(QIcon("E:/schm_menubg.png"), "按钮菜单测试", this, SLOT(menuTest()));
    menu->addAction("编辑任务");
    menu->addAction("删除任务");
   // menu->addAction(QIcon("E:/schm_menubg.png"), "按钮菜单测试", this, SLOT(menuTest()));
   // ui->pushButton->setMenu(menu);

    ui->toolButton->setMenu(menu);
    ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup);

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
    _bottomWgt = new CBottomPlusWgt(this);
    _bottomWgt->setFixedWidth(300);
    _bottomWgt->show();

    // 测试
    Test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Test()
{

}

bool MainWindow::DeleteDir(QString &path)
{
    if (path.isEmpty())
    {
        return false;
    }

    QDir dir(path);
    if (!dir.exists())
    {
        return true;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
        {
            fi.dir().remove(fi.fileName());
        }
        else
        {
            DeleteDir(fi.absoluteFilePath());
        }
    }

    return dir.rmpath(dir.absolutePath());
}

void MainWindow::changeResources()
{
    // 读取态势资源数据
    QString filepath = "E:/resources.xml";

    QFile file(filepath);
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        return;
    }

    unsigned int id = 0;
    QDomElement root = doc.documentElement();
    QDomElement taskele = root.firstChildElement("task");
    while (!taskele.isNull())
    {
        // 读取资源项
        QDomElement rescele = taskele.firstChildElement("item");
        while (!rescele.isNull())
        {

            // 记录信息
            rescele.setAttribute("id", id);
            id++;

            rescele = rescele.nextSiblingElement("item");
        }

        taskele = taskele.nextSiblingElement("task");
    }


    // 写入文档
    file.resize(0);
    QTextStream out_stream(&file);
    doc.save(out_stream, 4);
    file.flush();
    file.close();
}

void MainWindow::menuTest()
{
    //int i = 0;
    QString strNewTxt = "123";
    _bottomWgt->setText(strNewTxt);
    //_bottomWgt->resize();
}

void MainWindow::textChanged()
{
    _bottomWgt->setText(ui->textEdit->toPlainText());
    _bottomWgt->adjustSize();
    //_bottomWgt->setFixedWidth(300);
}

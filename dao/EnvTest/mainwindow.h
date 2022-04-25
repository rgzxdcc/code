#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class CBottomPlusWgt;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Test();

    bool DeleteDir(QString &path);

protected slots:

    void changeResources();

    void menuTest();

    void textChanged();

private:
    Ui::MainWindow *ui;

    CBottomPlusWgt *_bottomWgt;
};

#endif // MAINWINDOW_H

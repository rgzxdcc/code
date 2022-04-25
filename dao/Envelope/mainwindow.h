#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SituationScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Init();

private:
    Ui::MainWindow *ui;

    SituationScene *    _ss;
};

#endif // MAINWINDOW_H

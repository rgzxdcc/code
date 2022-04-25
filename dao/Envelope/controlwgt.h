#ifndef CONTROLWGT_H
#define CONTROLWGT_H

#include <QWidget>

class SituationScene;

namespace Ui {
class controlwgt;
}

// 干扰机控制界面
class controlwgt : public QWidget
{
    Q_OBJECT

public:
    explicit controlwgt(SituationScene *ss, QWidget *parent = 0);
    ~controlwgt();

protected Q_SLOTS:

    void slot_valuechanged();

private:
    Ui::controlwgt *ui;

    SituationScene * _ss;   // 态势场景
};

#endif // CONTROLWGT_H

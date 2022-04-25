#ifndef CBOTTOMPLUSWGT_H
#define CBOTTOMPLUSWGT_H

#include <QWidget>

namespace Ui {
class CBottomPlusWgt;
}

class CBottomPlusWgt : public QWidget
{
    Q_OBJECT

public:
    explicit CBottomPlusWgt(QWidget *parent = 0);
    ~CBottomPlusWgt();

    void setText(QString str);

private:
    Ui::CBottomPlusWgt *ui;
};

#endif // CBOTTOMPLUSWGT_H

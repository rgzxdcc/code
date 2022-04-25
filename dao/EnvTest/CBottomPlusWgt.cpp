#include "CBottomPlusWgt.h"
#include "ui_CBottomPlusWgt.h"

CBottomPlusWgt::CBottomPlusWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CBottomPlusWgt)
{
    ui->setupUi(this);
}

CBottomPlusWgt::~CBottomPlusWgt()
{
    delete ui;
}

void CBottomPlusWgt::setText(QString str)
{
    ui->label->setText(str);
}

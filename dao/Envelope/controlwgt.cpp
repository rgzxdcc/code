#include "controlwgt.h"
#include "ui_controlwgt.h"
#include "datadef.h"

#include "situationscene.h"

controlwgt::controlwgt(SituationScene *ss, QWidget *parent) :
    _ss(ss),
    QWidget(parent),
    ui(new Ui::controlwgt)
{
    ui->setupUi(this);

    // init signals and slots
    connect(ui->dsb_jamlon1, SIGNAL(valueChanged(double)), this, SLOT(slot_valuechanged()));
    connect(ui->dsb_jamlon2, SIGNAL(valueChanged(double)), this, SLOT(slot_valuechanged()));
    connect(ui->dsb_jamlat1, SIGNAL(valueChanged(double)), this, SLOT(slot_valuechanged()));
    connect(ui->dsb_jamlat2, SIGNAL(valueChanged(double)), this, SLOT(slot_valuechanged()));
    connect(ui->sb_jamalt1, SIGNAL(valueChanged(int)), this, SLOT(slot_valuechanged()));
    connect(ui->sb_jamalt2, SIGNAL(valueChanged(int)), this, SLOT(slot_valuechanged()));
}

controlwgt::~controlwgt()
{
    delete ui;
}

void controlwgt::slot_valuechanged()
{
    std::list<JamData> jams;
    JamData jd1;
    jd1.lon = ui->dsb_jamlon1->text().toDouble();
    jd1.lat = ui->dsb_jamlat1->text().toDouble();
    jd1.alt = ui->sb_jamalt1->text().toInt();
    jams.push_back(jd1);

    JamData jd2;
    jd2.lon = ui->dsb_jamlon2->text().toDouble();
    jd2.lat = ui->dsb_jamlat2->text().toDouble();
    jd2.alt = ui->sb_jamalt2->text().toInt();
    jams.push_back(jd2);

    _ss->UpdateJams(jams);
}

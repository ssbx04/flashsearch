#include "donneescorrompues.h"
#include "ui_donneescorrompues.h"

DonneesCorrompues::DonneesCorrompues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DonneesCorrompues)
{
    ui->setupUi(this);
}

DonneesCorrompues::~DonneesCorrompues()
{
    delete ui;
}

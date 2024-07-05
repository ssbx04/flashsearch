#include "basenonchargee.h"
#include "ui_basenonchargee.h"

BaseNonChargee::BaseNonChargee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseNonChargee)
{
    ui->setupUi(this);
}

BaseNonChargee::~BaseNonChargee()
{
    delete ui;
}

#include "basesauvegardee.h"
#include "ui_basesauvegardee.h"

BaseSauvegardee::BaseSauvegardee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseSauvegardee)
{
    ui->setupUi(this);
}

BaseSauvegardee::~BaseSauvegardee()
{
    delete ui;
}

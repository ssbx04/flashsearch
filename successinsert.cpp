#include "successinsert.h"
#include "ui_successinsert.h"

SuccessInsert::SuccessInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SuccessInsert)
{
    ui->setupUi(this);
}

SuccessInsert::~SuccessInsert()
{
    delete ui;
}

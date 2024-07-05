#include "failedinsert.h"
#include "ui_failedinsert.h"

FailedInsert::FailedInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FailedInsert)
{
    ui->setupUi(this);
}

FailedInsert::~FailedInsert()
{
    delete ui;
}

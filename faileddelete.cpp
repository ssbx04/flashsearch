#include "faileddelete.h"
#include "ui_faileddelete.h"

FailedDelete::FailedDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FailedDelete)
{
    ui->setupUi(this);
}

FailedDelete::~FailedDelete()
{
    delete ui;
}

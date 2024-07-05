#include "successdelete.h"
#include "ui_successdelete.h"

SuccessDelete::SuccessDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SuccessDelete)
{
    ui->setupUi(this);
}

SuccessDelete::~SuccessDelete()
{
    delete ui;
}

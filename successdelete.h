#ifndef SUCCESSDELETE_H
#define SUCCESSDELETE_H

#include <QDialog>

namespace Ui {
class SuccessDelete;
}

class SuccessDelete : public QDialog
{
    Q_OBJECT

public:
    explicit SuccessDelete(QWidget *parent = 0);
    ~SuccessDelete();

private:
    Ui::SuccessDelete *ui;
};

#endif // SUCCESSDELETE_H

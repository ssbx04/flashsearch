#ifndef FAILEDDELETE_H
#define FAILEDDELETE_H

#include <QDialog>

namespace Ui {
class FailedDelete;
}

class FailedDelete : public QDialog
{
    Q_OBJECT

public:
    explicit FailedDelete(QWidget *parent = 0);
    ~FailedDelete();

private:
    Ui::FailedDelete *ui;
};

#endif // FAILEDDELETE_H

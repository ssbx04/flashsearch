#ifndef FAILEDINSERT_H
#define FAILEDINSERT_H

#include <QDialog>

namespace Ui {
class FailedInsert;
}

class FailedInsert : public QDialog
{
    Q_OBJECT

public:
    explicit FailedInsert(QWidget *parent = 0);
    ~FailedInsert();

private:
    Ui::FailedInsert *ui;
};

#endif // FAILEDINSERT_H

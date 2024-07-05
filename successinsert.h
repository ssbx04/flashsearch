#ifndef SUCCESSINSERT_H
#define SUCCESSINSERT_H

#include <QDialog>

namespace Ui {
class SuccessInsert;
}

class SuccessInsert : public QDialog
{
    Q_OBJECT

public:
    explicit SuccessInsert(QWidget *parent = 0);
    ~SuccessInsert();

private:
    Ui::SuccessInsert *ui;
};

#endif // SUCCESSINSERT_H

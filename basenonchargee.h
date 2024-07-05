#ifndef BASENONCHARGEE_H
#define BASENONCHARGEE_H

#include <QDialog>

namespace Ui {
class BaseNonChargee;
}

class BaseNonChargee : public QDialog
{
    Q_OBJECT

public:
    explicit BaseNonChargee(QWidget *parent = 0);
    ~BaseNonChargee();

private:
    Ui::BaseNonChargee *ui;
};

#endif // BASENONCHARGEE_H

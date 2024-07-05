#ifndef BASESAUVEGARDEE_H
#define BASESAUVEGARDEE_H

#include <QDialog>

namespace Ui {
class BaseSauvegardee;
}

class BaseSauvegardee : public QDialog
{
    Q_OBJECT

public:
    explicit BaseSauvegardee(QWidget *parent = 0);
    ~BaseSauvegardee();

private:
    Ui::BaseSauvegardee *ui;
};

#endif // BASESAUVEGARDEE_H

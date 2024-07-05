#ifndef DONNEESCORROMPUES_H
#define DONNEESCORROMPUES_H

#include <QDialog>

namespace Ui {
class DonneesCorrompues;
}

class DonneesCorrompues : public QDialog
{
    Q_OBJECT

public:
    explicit DonneesCorrompues(QWidget *parent = 0);
    ~DonneesCorrompues();

private:
    Ui::DonneesCorrompues *ui;
};

#endif // DONNEESCORROMPUES_H

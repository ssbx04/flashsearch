#ifndef COMPAREHASHHASH_H
#define COMPAREHASHHASH_H

#include <QDialog>
#include <QStandardPaths>
#include "tablehash.h"
#include "dbheader.h"
namespace Ui {
class CompareHashHash;
}

class CompareHashHash : public QDialog
{
    Q_OBJECT

public:
    explicit CompareHashHash(QWidget *parent = 0);
    ~CompareHashHash();

private slots:
    void on_btn_comparer2_clicked();

private:
    Ui::CompareHashHash *ui;
    QString db_path;
};

#endif // COMPAREHASHHASH_H

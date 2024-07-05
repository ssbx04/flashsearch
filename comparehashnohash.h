#ifndef COMPAREHASHNOHASH_H
#define COMPAREHASHNOHASH_H

#include <QDialog>
#include <QStandardPaths>
#include "tablehash.h"
#include "dbheader.h"
namespace Ui {
class CompareHashNoHash;
}

class CompareHashNoHash : public QDialog
{
    Q_OBJECT

public:
    explicit CompareHashNoHash(QWidget *parent = 0);
    ~CompareHashNoHash();

private slots:
    void on_btn_comparer1_clicked();

private:
    Ui::CompareHashNoHash *ui;
    QString db_path;
};

#endif // COMPAREHASHNOHASH_H

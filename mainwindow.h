#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include "DBHeader.h"
#include "tablehash.h"
#include "faileddelete.h"
#include "failedinsert.h"
#include "successdelete.h"
#include "successinsert.h"
#include "comparehashnohash.h"
#include "comparehashhash.h"
#include "basenonchargee.h"
#include "basesauvegardee.h"
#include "donneescorrompues.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionInserer_triggered();

    void on_actionSupprimer_triggered();

    void on_backSupp_clicked();

    void on_btn_inserer_clicked();

    void on_backRec_clicked();

    void on_actionRechercher_triggered();

    void on_actionQuitter_triggered();

    void on_actionCharger_triggered();

    void on_actionSauvegarder_triggered();

    void on_btn_rechercher_clicked();

    void on_backAff_clicked();

    void on_actionAfficher_triggered();

    void on_backSize_clicked();

    void on_actionTaille_triggered();

    void on_btn_supprimer_clicked();

    void on_actionFonction_1_triggered();

    void on_actionFonction_2_triggered();

    void on_actionFonction_3_triggered();

    void on_actionSans_Hachage_triggered();

    void on_actionHachage_Sans_Hachage_triggered();

    void on_actionHachage_fi_Hachage_fj_triggered();

    void on_actionPage_Aide_triggered();

private:
    Ui::MainWindow *ui;
    TableHash tabHash;
    QString *added_keys;
    QString *deleted_keys;
    int add_array_tracker;
    int delete_array_tracker;
    QSqlQueryModel *model;
    int HashFunctionIndex;

    FailedDelete *f_delete;
    FailedInsert *f_insert;
    SuccessDelete *s_delete;
    SuccessInsert *s_insert;

    CompareHashNoHash *compare1;
    CompareHashHash *compare2;

    bool isCharged;

    BaseNonChargee *bnc;
    BaseSauvegardee *bs;
    DonneesCorrompues *dc;
    QString db_path;

};

#endif // MAINWINDOW_H

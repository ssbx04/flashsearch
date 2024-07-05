#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tabHash (1000)
{

    ui->setupUi(this);

    added_keys = new QString[1000];
    deleted_keys = new QString[1000];
    add_array_tracker = 0;
    delete_array_tracker = 0;
    model = NULL;
    HashFunctionIndex = 1;

    ui->lineMatriInsert->setPlaceholderText("Matricule de la structure");
    ui->lineNomiInsert->setPlaceholderText("Nom de la structure");
    ui->lineSecteurInsert->setPlaceholderText("Secteur de la structure");
    ui->lineSiteInsert->setPlaceholderText("Site web de la structure");
    ui->lineDescInsert->setPlaceholderText("Nom de la structure");
    ui->lineMatSupp->setPlaceholderText("Matricule de la structure");
    ui-> lineMatRec->setPlaceholderText("Matricule de la structure");

    f_delete = new FailedDelete();
    f_insert = new FailedInsert();
    s_delete = new SuccessDelete();
    s_insert = new SuccessInsert();

    compare1 = new CompareHashNoHash();
    compare2 = new CompareHashHash();

    isCharged = false;

    db_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/database.db";

    bnc = new BaseNonChargee();
    bs = new BaseSauvegardee();
    dc = new DonneesCorrompues();
}

MainWindow::~MainWindow()
{
    delete added_keys;
    delete deleted_keys;
    delete model;
    delete f_delete;
    delete f_insert;
    delete s_delete;
    delete s_insert;
    delete compare1;
    delete compare2;
    delete bnc;
    delete bs;
    delete dc;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionInserer_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionSupprimer_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_backSupp_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_backRec_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionRechercher_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_backAff_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_backSize_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_actionHachage_Sans_Hachage_triggered()
{
    compare1->showMaximized();
}
void MainWindow::on_actionHachage_fi_Hachage_fj_triggered()
{
    compare2->showMaximized();
}
void MainWindow::on_actionPage_Aide_triggered()
{
      ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_actionCharger_triggered()
{
    if(!isCharged){
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(db_path);
        if(!QFile::exists(db_path))
            return;
        if(!database.open())
            return;
        QSqlQuery query(database);
        query.prepare("select * from Structure");
        query.exec();
        while(query.next()){
            QString cle = query.value(0).toString();
            QString nom = query.value(1).toString();
            QString secteur = query.value(2).toString();
            QString site = query.value(3).toString();
            QString description = query.value(4).toString();
            tabHash.Insertion(cle,nom,secteur,site,description,HashFunctionIndex);
        }
         database.close();
        isCharged = true;
        ui->txtCharge->setText("Base Chargée");
        ui->txtHashFunction->setText("Fonction 1");
    }
    else{
        bnc->show();
    }
}

void MainWindow::on_actionQuitter_triggered()
{
    exit(0);
}

void MainWindow::on_btn_inserer_clicked()
{
    if(isCharged){
        QString matricule = ui->lineMatriInsert->text();
        QString nom = ui->lineNomiInsert->text();
        QString secteur = ui->lineSecteurInsert->text();
        QString site = ui->lineSiteInsert->text();
        QString description = ui->lineDescInsert->toPlainText();
        if((matricule == "") || (nom == "") || (secteur == "") || (site == "") || (description == "")){
            dc->show();
        }
        else{
            bool insertion_state = tabHash.Insertion(matricule,nom,secteur,site,description,HashFunctionIndex);
            ui->lineMatriInsert->setText("");
            ui->lineNomiInsert->setText("");
            ui->lineSecteurInsert->setText("");
            ui->lineSiteInsert->setText("");
            ui->lineDescInsert->setPlainText("");
            if(insertion_state){
                int i = 0;
                while(i < delete_array_tracker && deleted_keys[i] != matricule)
                    i++;
                if(i < delete_array_tracker){
                    //Donc on doit le supprimer et ne pas faire d'insertion
                    for (int j = i; j < delete_array_tracker - 1; ++j)
                        deleted_keys[j] = deleted_keys[j + 1];
                    delete_array_tracker--;
                }
                else{
                    //On doit faire l'insertion
                    int k = 0;
                    while(k < add_array_tracker && matricule != added_keys[k])
                        k++;
                    if(k >= add_array_tracker){
                        added_keys[add_array_tracker++] = matricule;
                    }
                }
                s_insert->show();
            }
            else{
                f_insert->show();
            }
        }
    }
    else{
        bnc->show();
    }
}
void MainWindow::on_actionSauvegarder_triggered(){
    if(isCharged){
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(db_path);
        if(!QFile::exists(db_path))
            return;
        if(!database.open())
            return;
        QSqlQuery query(database);
        for (int i = 0; i < delete_array_tracker; ++i){
            query.prepare("delete from structure where matricule = '" + deleted_keys[i] + "' ");
            query.exec();
        }
        QString nom,secteur,site,description;
        Value val;
        for (int i = 0; i < add_array_tracker; ++i) {
            QString cle = added_keys[i];
            val = tabHash.Get(cle,HashFunctionIndex);
            nom = val.nom;
            secteur = val.secteur;
            site = val.site;
            description = val.description;
            query.prepare("insert into structure values ('" + cle + "','" + nom + "','" + secteur + "','" + site + "','" + description + "')");
            query.exec();
        }
        if(added_keys){
            for(int i = 0; i < add_array_tracker; i++)
                added_keys[i] = "";
            add_array_tracker = 0;
        }
        if(deleted_keys){
            for(int i = 0; i < delete_array_tracker; i++)
                deleted_keys[i] = "";
            delete_array_tracker = 0;
        }
        bs->show();
        database.close();
    }
    else{
        bnc->show();
    }
}

void MainWindow::on_btn_rechercher_clicked()
{
    if(isCharged){
        QString res_val = ui->lineMatRec->text();
        if(res_val == ""){
            dc->show();
        }
        else{
            Value v = tabHash.Get(res_val,HashFunctionIndex);
            if(v.nom == "undefined key"){
                QString nores = "Structure non trouvée!";
                ui->res_no_mat->setText(nores);
                ui->res_nom->setText("");
                ui->res_secteur->setText("");
                ui->res_site->setText("");
                ui->res_desc->setText("");
            }
            else{
                QString mat = "Matricule : " + res_val;
                QString nom = "Nom : " + v.nom;
                QString sect = "Secteur : " + v.secteur;
                QString site = "Site : " + v.site;
                QString desc = "Description : " + v.description;
                ui->res_no_mat->setText(mat);
                ui->res_nom->setText(nom);
                ui->res_secteur->setText(sect);
                ui->res_site->setText(site);
                ui->res_desc->setWordWrap(true);
                ui->res_desc->setText(desc);
            }
        }
    }
    else{
        bnc->show();
    }
}

void MainWindow::on_actionAfficher_triggered()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(db_path);
    if(!QFile::exists(db_path))
        return;
    if(!database.open())
        return;
    QSqlQuery query(database);
    query.prepare("select * from structure");
    query.exec();
    if(model == NULL){
        model = new QSqlQueryModel();
    }
    model->setQuery("select * from structure");
    ui->DisplayBDD->setModel(model);
    ui->DisplayBDD->setColumnWidth(0,200);
    ui->DisplayBDD->setColumnWidth(1,200);
    ui->DisplayBDD->setColumnWidth(2,200);
    ui->DisplayBDD->setColumnWidth(3,200);
    ui->DisplayBDD->setColumnWidth(4,200);
    database.close();
    ui->stackedWidget->setCurrentIndex(4);
}



void MainWindow::on_actionTaille_triggered()
{
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(db_path);
        if(!QFile::exists(db_path))
            return;
        if(!database.open())
            return;
        QSqlQuery query(database);
        query.prepare("select count(*) from structure");
        query.exec();
        query.next();
        QString taille = query.value(0).toString();
        ui->txtTaille->setText(taille);
        ui->stackedWidget->setCurrentIndex(5);
        database.close();
}

void MainWindow::on_btn_supprimer_clicked()
{
    if(isCharged){
        QString matricule_rec = ui->lineMatSupp->text();
        if(matricule_rec == ""){
            dc->show();
        }
        else{
            bool suppression_state = tabHash.Suppression(matricule_rec,HashFunctionIndex);
            ui->lineMatSupp->setText("");
            if(suppression_state){
                int i = 0;
                while(i < add_array_tracker && added_keys[i] != matricule_rec)
                    i++;
                if(i < add_array_tracker){
                    //Donc on doit le supprimer et ne pas faire de supression
                    for (int j = i; j < add_array_tracker - 1; ++j)
                        added_keys[j] = added_keys[j + 1];
                    add_array_tracker--;
                }
                else{
                    //On doit faire l'insertion
                    int k = 0;
                    while(k < delete_array_tracker && matricule_rec != deleted_keys[k])
                        k++;
                    if(k >= delete_array_tracker){
                        deleted_keys[delete_array_tracker++] = matricule_rec;
                    }
                }
                s_delete->show();
            }
            else{
                f_delete->show();
            }
        }
    }
    else{
        bnc->show();
    }
}

void MainWindow::on_actionFonction_1_triggered()
{
    if(!isCharged){
        isCharged = true;
        ui->txtCharge->setText("Base Chargée");
    }
    HashFunctionIndex = 1;
    ui->txtHashFunction->setText("Fonction 1");
    tabHash.detruire_table();
    for(int i = 0; i < add_array_tracker; i++)
        added_keys[i] = "";
    add_array_tracker = 0;

    for(int i = 0; i < delete_array_tracker; i++)
        deleted_keys[i] = "";
    delete_array_tracker = 0;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(db_path);
    if(!QFile::exists(db_path))
        return;
    if(!database.open())
        return;
    QSqlQuery query(database);
    query.prepare("select * from Structure");
    query.exec();
    while(query.next()){
        QString cle = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString secteur = query.value(2).toString();
        QString site = query.value(3).toString();
        QString description = query.value(4).toString();
        tabHash.Insertion(cle,nom,secteur,site,description,HashFunctionIndex);
    }
     database.close();

}

void MainWindow::on_actionFonction_2_triggered()
{
    if(!isCharged){
        isCharged = true;
        ui->txtCharge->setText("Base Chargée");
    }
    HashFunctionIndex = 2;
    ui->txtHashFunction->setText("Fonction 2");
    tabHash.detruire_table();
    for(int i = 0; i < add_array_tracker; i++)
        added_keys[i] = "";
    add_array_tracker = 0;
    for(int i = 0; i < delete_array_tracker; i++)
        deleted_keys[i] = "";
    delete_array_tracker = 0;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(db_path);
    if(!QFile::exists(db_path))
        return;
    if(!database.open())
        return;
    QSqlQuery query(database);
    query.prepare("select * from Structure");
    query.exec();
    while(query.next()){
        QString cle = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString secteur = query.value(2).toString();
        QString site = query.value(3).toString();
        QString description = query.value(4).toString();
        tabHash.Insertion(cle,nom,secteur,site,description,HashFunctionIndex);
    }

     database.close();

}

void MainWindow::on_actionFonction_3_triggered()
{
    if(!isCharged){
        isCharged = true;
        ui->txtCharge->setText("Base Chargée");
    }
    HashFunctionIndex = 3;
    ui->txtHashFunction->setText("Fonction 3");
    tabHash.detruire_table();
    for(int i = 0; i < add_array_tracker; i++)
        added_keys[i] = "";
    add_array_tracker = 0;

    for(int i = 0; i < delete_array_tracker; i++)
        deleted_keys[i] = "";
    delete_array_tracker = 0;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(db_path);
    if(!QFile::exists(db_path))
        return;
    if(!database.open())
        return;
    QSqlQuery query(database);
    query.prepare("select * from Structure");
    query.exec();
    while(query.next()){
        QString cle = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString secteur = query.value(2).toString();
        QString site = query.value(3).toString();
        QString description = query.value(4).toString();
        tabHash.Insertion(cle,nom,secteur,site,description,HashFunctionIndex);
    }
     database.close();

}

void MainWindow::on_actionSans_Hachage_triggered()
{
    if(!isCharged){
        isCharged = true;
        ui->txtCharge->setText("Base Chargée");
    }
    HashFunctionIndex = 4;
    ui->txtHashFunction->setText("Sans Hachage");
    tabHash.detruire_table();
    for(int i = 0; i < add_array_tracker; i++)
        added_keys[i] = "";
    add_array_tracker = 0;

    for(int i = 0; i < delete_array_tracker; i++)
        deleted_keys[i] = "";
    delete_array_tracker = 0;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(db_path);
    if(!QFile::exists(db_path))
        return;
    if(!database.open())
        return;
    QSqlQuery query(database);
    query.prepare("select * from Structure");
    query.exec();
    while(query.next()){
        QString cle = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString secteur = query.value(2).toString();
        QString site = query.value(3).toString();
        QString description = query.value(4).toString();
        tabHash.Insertion(cle,nom,secteur,site,description,HashFunctionIndex);
    }
     database.close();

}


#include <chrono>
#include "comparehashhash.h"
#include "ui_comparehashhash.h"
#include "qcustomplot.h"
CompareHashHash::CompareHashHash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompareHashHash)
{
    ui->setupUi(this);
    db_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/database.db";
    ui->plot2->xAxis->setTickLabelColor(QColor(246, 182, 24));
    ui->plot2->xAxis->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot2->xAxis->setLabelColor(QColor(246, 182, 24));
    ui->plot2->xAxis->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot2->xAxis->setSubTickPen(QPen(QColor(246, 182, 24)));
    ui->plot2->xAxis->grid()->setPen(QPen(QColor(246, 182, 24)));
    ui->plot2->xAxis->grid()->setSubGridPen(QPen(QColor(246, 182, 24)));

    ui->plot2->xAxis2->setTickLabelColor(QColor(246, 182, 24));
    ui->plot2->xAxis2->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot2->xAxis2->setLabelColor(QColor(246, 182, 24));
    ui->plot2->xAxis2->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot2->xAxis2->setSubTickPen(QPen(QColor(246, 182, 24)));

    ui->plot2->yAxis->setTickLabelColor(QColor(246, 182, 24));
    ui->plot2->yAxis->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot2->yAxis->setLabelColor(QColor(246, 182, 24));
    ui->plot2->yAxis->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot2->yAxis->setSubTickPen(QPen(QColor(246, 182, 24)));
    ui->plot2->yAxis->grid()->setPen(QPen(QColor(246, 182, 24)));
    ui->plot2->yAxis->grid()->setSubGridPen(QPen(QColor(246, 182, 24)));

    ui->plot2->yAxis2->setTickLabelColor(QColor(246, 182, 24));
    ui->plot2->yAxis2->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot2->yAxis2->setLabelColor(QColor(246, 182, 24));
    ui->plot2->yAxis2->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot2->yAxis2->setSubTickPen(QPen(QColor(246, 182, 24)));

}

CompareHashHash::~CompareHashHash()
{
    delete ui;
}

void CompareHashHash::on_btn_comparer2_clicked()
{
    QString funcChoice1 = ui->choixFunFuncCmp->currentText();
    QString funcChoice2 = ui->choixFunFuncCmp2->currentText();
    TableHash func_hash1(1000);
    TableHash func_hash2(1000);
    QVector<double> x(1000), y(1000);
    QVector<double> x1(1000), y1(1000);
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(db_path);
    if(!QFile::exists(db_path))
        return;
    if(!database.open())
        return;
    int i = 0;
    QSqlQuery query(database);
    query.prepare("select * from Structure");
    query.exec();
    while(query.next() && i < 1000){
        QString cle = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString secteur = query.value(2).toString();
        QString site = query.value(3).toString();
        QString description = query.value(4).toString();

        if(funcChoice1 == "Fonction 1")
             func_hash1.Insertion(cle,nom,secteur,site,description,1);
        else if(funcChoice1 == "Fonction 2")
            func_hash1.Insertion(cle,nom,secteur,site,description,2);
        else
            func_hash1.Insertion(cle,nom,secteur,site,description,3);

        if(funcChoice2 == "Fonction 1")
            func_hash2.Insertion(cle,nom,secteur,site,description,1);
        else if(funcChoice2 == "Fonction 2")
            func_hash2.Insertion(cle,nom,secteur,site,description,2);
        else
            func_hash2.Insertion(cle,nom,secteur,site,description,3);
        i++;
    }
    i = 0;
    query.clear();
    query.prepare("select * from Structure");
    query.exec();
    while(query.next()){
        QString sr = query.value(0).toString();
        //qDebug() << "Sr : " << sr;
        std::chrono::steady_clock::time_point start2;
        std::chrono::steady_clock::time_point stop2;

        if(funcChoice2 == "Fonction 1"){
            start2 = std::chrono::steady_clock::now();
            func_hash2.Contient(sr,1);
            stop2 = std::chrono::steady_clock::now();
        }
        else if(funcChoice2 == "Fonction 2"){
            start2 = std::chrono::steady_clock::now();
            func_hash2.Contient(sr,2);
            stop2 = std::chrono::steady_clock::now();
        }
        else{
            start2 = std::chrono::steady_clock::now();
            func_hash2.Contient(sr,3);
            stop2 = std::chrono::steady_clock::now();
        }

        auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);
        y1.push_back(duration2.count());


        std::chrono::steady_clock::time_point start1;
        std::chrono::steady_clock::time_point stop1;

        if(funcChoice1 == "Fonction 1"){
            start1 = std::chrono::steady_clock::now();
            func_hash1.Contient(sr,1);
            stop1 = std::chrono::steady_clock::now();
        }
        else if(funcChoice1 == "Fonction 2"){
            start1 = std::chrono::steady_clock::now();
            func_hash1.Contient(sr,2);
            stop1 = std::chrono::steady_clock::now();
        }
        else{
            start1 = std::chrono::steady_clock::now();
            func_hash1.Contient(sr,3);
            stop1 = std::chrono::steady_clock::now();
        }
        auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);
        y.push_back(duration1.count());
        x.push_back(i+1);
        x1.push_back(i+1);
        i++;
    }
        qDebug() << "Lignes gauche : " << func_hash1.Taille() << " | Lignes droite : " << func_hash2.Taille();
        ui->plot2->addGraph();
        ui->plot2->graph(0)->setData(x, y);
        if(funcChoice1 == "Fonction 1")
            ui->plot2->graph(0)->setPen(QPen(QColor(255, 0, 0)));
        else if(funcChoice1 == "Fonction 2")
            ui->plot2->graph(0)->setPen(QPen(QColor(0,255, 0)));
        else
            ui->plot2->graph(0)->setPen(QPen(QColor(0,0, 255)));
        ui->plot2->addGraph();
        ui->plot2->graph(1)->setData(x1, y1);

        if(funcChoice2 == "Fonction 1")
            ui->plot2->graph(1)->setPen(QPen(QColor(255, 0, 0)));
        else if(funcChoice2 == "Fonction 2")
            ui->plot2->graph(1)->setPen(QPen(QColor(0,255, 0)));
        else
            ui->plot2->graph(1)->setPen(QPen(QColor(0,0, 255)));

        ui->plot2->xAxis->setLabel("Nombre d'ajouts");
        ui->plot2->yAxis->setLabel("Temps d'execution");
        ui->plot2->xAxis->setRange(0, 1000);
        ui->plot2->yAxis->setRange(0, 10000);
        ui->plot2->replot();
    database.close();
}

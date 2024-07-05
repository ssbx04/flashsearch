#include <chrono>
#include "comparehashnohash.h"
#include "ui_comparehashnohash.h"
#include "qcustomplot.h"
CompareHashNoHash::CompareHashNoHash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompareHashNoHash)
{
    ui->setupUi(this);
    db_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/database.db";

    ui->plot->xAxis->setTickLabelColor(QColor(246, 182, 24));
    ui->plot->xAxis->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot->xAxis->setLabelColor(QColor(246, 182, 24));
    ui->plot->xAxis->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot->xAxis->setSubTickPen(QPen(QColor(246, 182, 24)));
    ui->plot->xAxis->grid()->setPen(QPen(QColor(246, 182, 24)));
    ui->plot->xAxis->grid()->setSubGridPen(QPen(QColor(246, 182, 24)));

    ui->plot->xAxis2->setTickLabelColor(QColor(246, 182, 24));
    ui->plot->xAxis2->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot->xAxis2->setLabelColor(QColor(246, 182, 24));
    ui->plot->xAxis2->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot->xAxis2->setSubTickPen(QPen(QColor(246, 182, 24)));

    ui->plot->yAxis->setTickLabelColor(QColor(246, 182, 24));
    ui->plot->yAxis->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot->yAxis->setLabelColor(QColor(246, 182, 24));
    ui->plot->yAxis->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot->yAxis->setSubTickPen(QPen(QColor(246, 182, 24)));
    ui->plot->yAxis->grid()->setPen(QPen(QColor(246, 182, 24)));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(246, 182, 24)));

    ui->plot->yAxis2->setTickLabelColor(QColor(246, 182, 24));
    ui->plot->yAxis2->setBasePen(QPen(QColor(246, 182, 24)));
    ui->plot->yAxis2->setLabelColor(QColor(246, 182, 24));
    ui->plot->yAxis2->setTickPen(QPen(QColor(246, 182, 24)));
    ui->plot->yAxis2->setSubTickPen(QPen(QColor(246, 182, 24)));
}

CompareHashNoHash::~CompareHashNoHash()
{
    delete ui;
}

void CompareHashNoHash::on_btn_comparer1_clicked()
{
    QString funcChoice = ui->choixFuncCmp1->currentText();
    TableHash func_hash(1000);
    TableHash func_no_hash(1000);
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(db_path);
    if(!QFile::exists(db_path))
        return;
    if(!database.open())
        return;
    QSqlQuery query(database);
    query.prepare("select * from Structure");
    query.exec();
    QVector<double> x(1000), y(1000);
    QVector<double> x1(1000), y1(1000);
    int i = 0;
    while(query.next()  && i < 1000){
        QString cle = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString secteur = query.value(2).toString();
        QString site = query.value(3).toString();
        QString description = query.value(4).toString();
        if(funcChoice == "Fonction 1")
            func_hash.Insertion(cle,nom,secteur,site,description,1);
        else if(funcChoice == "Fonction 2")
            func_hash.Insertion(cle,nom,secteur,site,description,2);
        else
            func_hash.Insertion(cle,nom,secteur,site,description,3);

        func_no_hash.Insertion(cle,nom,secteur,site,description,4);
        i++;
    }
    query.clear();
    query.prepare("select * from Structure");
    query.exec();
    i = 0;
    while(query.next()){
        QString sr = query.value(0).toString();
        std::chrono::steady_clock::time_point start1;
        std::chrono::steady_clock::time_point stop1;

        if(funcChoice == "Fonction 1"){
            start1 = std::chrono::steady_clock::now();
            func_hash.Contient(sr,1);
            stop1 = std::chrono::steady_clock::now();
        }
        else if(funcChoice == "Fonction 2"){
            start1 = std::chrono::steady_clock::now();
            func_hash.Contient(sr,2);
            stop1 = std::chrono::steady_clock::now();
        }
        else{
            start1 = std::chrono::steady_clock::now();
            func_hash.Contient(sr,3);
            stop1 = std::chrono::steady_clock::now();
        }
        auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);
        y.push_back(duration1.count());


        std::chrono::steady_clock::time_point start2 = std::chrono::steady_clock::now();
        func_no_hash.Contient(sr,4);
        std::chrono::steady_clock::time_point stop2 = std::chrono::steady_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);
        y1.push_back(duration2.count());
        //qDebug() << "duration1 = " << duration1.count();
        //qDebug() << "duration2 = " << duration2.count();
        x.push_back(i+1);
        x1.push_back(i+1);
        i++;
    }
        ui->plot->addGraph();
        ui->plot->graph(0)->setData(x, y);
        if(funcChoice == "Fonction 1")
            ui->plot->graph(0)->setPen(QPen(QColor(255, 0, 0)));
        else if(funcChoice == "Fonction 2")
            ui->plot->graph(0)->setPen(QPen(QColor(0,255, 0)));
        else
            ui->plot->graph(0)->setPen(QPen(QColor(0,0, 255)));

        ui->plot->addGraph();
        ui->plot->graph(1)->setData(x1, y1);
        ui->plot->graph(1)->setPen(QPen(QColor(255,0, 255)));
        ui->plot->xAxis->setLabel("Nombre d'ajouts");
        ui->plot->yAxis->setLabel("Nombre d'iterations");
        ui->plot->xAxis->setRange(0, 1000);
        ui->plot->yAxis->setRange(0, 10000);
        ui->plot->replot();

        database.close();
}

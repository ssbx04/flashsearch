#ifndef TABLEHASH_H
#define TABLEHASH_H
#include <QString>
struct Value{
    QString nom;
    QString secteur;
    QString site;
    QString description;
};
struct Pair{
    QString cle;
    Value valeur;
};

struct node{
    Pair element;
    node *next;
};

class TableHash{
private:
    //friend class MainWindow;
    int taille_max;
    int taille_actuelle;
    node **table;
public:
    TableHash(int);
    ~TableHash();
    bool Insertion(QString,QString,QString,QString,QString,int);
    bool Suppression(QString,int);
    Value Get(QString,int);
    bool Contient(QString,int);
    int Taille();
    bool EstVide();
    int Hash1(QString);
    int Hash2(QString);
    int Hash3(QString);
    int NoHash(QString);
    void detruire_table();
};

#endif // TABLEHASH_H

#include "tablehash.h"
#include <QDebug>
#include <cmath>
TableHash::TableHash(int max) {
    taille_max = max;
    taille_actuelle = 0;
    table = new node *[taille_max];
    for(int i = 0; i < max ; i++)
        table[i] = NULL;
}
TableHash::~TableHash(){
    if(table){
        for(int i = 0; i < taille_max; i++){
            if(table[i] != NULL){
                while(table[i] != NULL){
                    node *temp = table[i];
                    table[i] = table[i]->next;
                    delete temp;
                    temp = NULL;
                }
            }
        }
        delete table;
    }
}
void TableHash::detruire_table(){
    for(int i = 0; i < taille_max; i++){
        if(table[i] != NULL){
            while(table[i] != NULL){
                node *temp = table[i];
                table[i] = table[i]->next;
                delete temp;
                temp = NULL;
            }
        }
    }
}

bool TableHash::Insertion(QString cle,QString nom,QString secteur,QString site,QString description,int hashFunc){
    if(taille_actuelle < taille_max){
        int index;
        switch (hashFunc) {
        case 1:
            index = Hash1(cle);
            break;
        case 2:
            index = Hash2(cle);
            break;
        case 3:
            index = Hash3(cle);
            break;
        case 4:
            index = 0;
            break;
        }
        if(!Contient(cle,index)){
            if(table[index] == NULL)
                taille_actuelle++;
            node *nouv = new node;
            nouv->element.cle = cle;
            nouv->element.valeur.nom = nom;
            nouv->element.valeur.secteur = secteur;
            nouv->element.valeur.site = site;
            nouv->element.valeur.description = description;
            nouv->next = NULL;
            if(table[index] == NULL)
                table[index] = nouv;
            else{
                node *current = table[index];
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = nouv;
            }
            return true;
        }
    }
    return false;
}

bool TableHash::Suppression(QString cle,int hashFunc){
    if(taille_actuelle > 0){
        int index;
        switch (hashFunc) {
        case 1:
            index = Hash1(cle);
            break;
        case 2:
            index = Hash2(cle);
            break;
        case 3:
            index = Hash3(cle);
            break;
        case 4:
            index = 0;
            break;
        }
        if(table[index]){
            if(table[index]->element.cle == cle){
                node *temp = table[index];
                table[index] = table[index]->next;
                delete temp;
                if(table[index] == NULL)
                    taille_actuelle--;
                return true;
            }
            else{
                qDebug() << index << "\n";
                node *current = table[index]->next, *precedent = current;
                while(current != NULL && current->element.cle != cle){
                    precedent = current;
                    current = current->next;
                }
                if(current){
                    precedent->next = current->next;
                    delete current;
                    return true;
                }
            }
        }
    }
    return false;
}
Value TableHash::Get(QString cle,int hashFunc){
    int index;
    switch (hashFunc) {
    case 1:
        index = Hash1(cle);
        break;
    case 2:
        index = Hash2(cle);
        break;
    case 3:
        index = Hash3(cle);
        break;
    case 4:
        index = 0;
        break;
    }
    node *current = table[index];
    while (current != NULL && current->element.cle != cle){
        current = current->next;
    }
    Value v;
    if(current){
        v.nom = current->element.valeur.nom;
        v.secteur = current->element.valeur.secteur;
        v.site = current->element.valeur.site;
        v.description = current->element.valeur.description;
    }
    else{
        v.nom = "undefined key";
        v.secteur = "undefined key";
        v.site = "undefined key";
        v.description = "undefined key";
    }
    return v;
}

bool TableHash::Contient(QString cle, int hashFunc){
    int index;
    switch (hashFunc) {
    case 1:
        index = Hash1(cle);
        break;
    case 2:
        index = Hash2(cle);
        break;
    case 3:
        index = Hash3(cle);
        break;
    case 4:
        index = 0;
        break;
    }
    node *current = table[index];
    while (current != NULL && current->element.cle != cle)
        current = current->next;
    if(current)
        return true;
    return false;

}
int TableHash::Taille(){
    return taille_actuelle;
}
bool TableHash::EstVide(){
    return taille_actuelle == 0;
}

int TableHash::Hash1(QString cle){
    int h,m=0;
    for(int i = 1; i <= cle.length(); i++)
        m += 256 * i * (int)cle.at(i - 1).toLatin1();
    h = m % taille_max;
    return h;
}

int TableHash::Hash2(QString cle){
    int sigma = 0;
    for(int i = 0; i < cle.length(); i++)
        sigma += (int) cle.at(i).toLatin1() * (i+1);
    return sigma % taille_max;
}

int TableHash::Hash3(QString cle){
    int sigma = 0;
    for(int i = 0; i < cle.length(); i++)
        sigma += (int) cle.at(i).toLatin1();
    return sigma % taille_max;
}

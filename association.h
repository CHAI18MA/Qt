#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

#include <QDebug>

class Association
{
public:
    Association();

    int getId_eleve() const;
    void setId_eleve(int value);

    int getId_activite() const;
    void setId_activite(int value);

    bool ajouter(QString matriculeEleve,QString matriculeActivite);
    QSqlQueryModel * afficher_inscri(QString matriculeEleve);
    QSqlQueryModel * afficher_non_inscri(QString matriculeEleve);
    bool supprimer(QString matriculeEleve,QString matriculeActivite);


private:
    int id_eleve;
    int id_activite;
};

#endif // ASSOCIATION_H

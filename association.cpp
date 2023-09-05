#include "association.h"

Association::Association()
{

}

int Association::getId_eleve() const
{
    return id_eleve;
}

void Association::setId_eleve(int value)
{
    id_eleve = value;
}

int Association::getId_activite() const
{
    return id_activite;
}

void Association::setId_activite(int value)
{
    id_activite = value;
}

bool Association::ajouter(QString matriculeEleve,QString matriculeActivite){
    QSqlQueryModel * modal=new QSqlQueryModel();

    modal->setQuery("SELECT ID FROM activite WHERE Matricule='"+matriculeActivite+"';");

    int id_activite = modal->record(0).value("id").toInt();

    modal->setQuery("SELECT ID FROM eleve WHERE Matricule='"+matriculeEleve+"';");

    int id_eleve = modal->record(0).value("id").toInt();

    QSqlQuery query;

    query.prepare("Insert Into ASSOCIATION(ID_ACTIVITE,ID_ELEVE) Values(:activite,:eleve);");
    query.bindValue(":activite",id_activite);
    query.bindValue(":eleve",id_eleve);


    return query.exec();
}

bool Association::supprimer(QString matriculeEleve,QString matriculeActivite){
    QSqlQueryModel * modal=new QSqlQueryModel();

    modal->setQuery("SELECT ID FROM activite WHERE Matricule='"+matriculeActivite+"';");

    int id_activite = modal->record(0).value("id").toInt();

    modal->setQuery("SELECT ID FROM eleve WHERE Matricule='"+matriculeEleve+"';");

    int id_eleve = modal->record(0).value("id").toInt();

    QSqlQuery query;

    query.prepare("DELETE FROM association WHERE id_eleve=:eleve and id_activite=:activite");
    query.bindValue(":eleve",id_eleve);
    query.bindValue(":activite",id_activite);

    return query.exec();
}

QSqlQueryModel * Association::afficher_inscri(QString matriculeEleve){
    QSqlQueryModel * modal=new QSqlQueryModel();

    modal->setQuery("SELECT ID FROM eleve WHERE Matricule='"+matriculeEleve+"';");

    QString id_eleve = modal->record(0).value("ID").toString();


    modal->setQuery("SELECT activite.MATRICULE,activite.TITRE,activite.TYPE,activite.DATE_ACTIVITE FROM activite JOIN association ON association.id_activite=activite.id WHERE activite.ARCHIVE=0 and association.id_eleve="+id_eleve+";");


    return modal;
}

QSqlQueryModel * Association::afficher_non_inscri(QString matriculeEleve){
    QSqlQueryModel * modal=new QSqlQueryModel();

    modal->setQuery("SELECT ID FROM eleve WHERE Matricule='"+matriculeEleve+"';");

    QString id_eleve = modal->record(0).value("ID").toString();

    modal->setQuery("SELECT activite.MATRICULE,activite.TITRE,activite.TYPE,activite.DATE_ACTIVITE FROM activite left JOIN association ON association.id_activite=activite.id and association.id_eleve="+id_eleve+" where association.id_eleve is null and activite.ARCHIVE=0;");

    return modal;
}

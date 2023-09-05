#include "eleve.h"

int Eleve::getId() const
{
    return id;
}

void Eleve::setId(int value)
{
    id = value;
}

QString Eleve::getNom() const
{
    return nom;
}

void Eleve::setNom(const QString &value)
{
    nom = value;
}

QDate Eleve::getDateNaissance() const
{
    return dateNaissance;
}

void Eleve::setDateNaissance(const QDate &value)
{
    dateNaissance = value;
}

QString Eleve::getEmail() const
{
    return email;
}

void Eleve::setEmail(const QString &value)
{
    email = value;
}

QString Eleve::getPrenom() const
{
    return prenom;
}

void Eleve::setPrenom(const QString &value)
{
    prenom = value;
}

QString Eleve::getMatricule() const
{
    return matricule;
}

void Eleve::setMatricule(const QString &value)
{
    matricule = value;
}

QString Eleve::getSexe() const
{
    return sexe;
}

void Eleve::setSexe(const QString &value)
{
    sexe = value;
}

Eleve::Eleve()
{

}

bool Eleve::ajouter(){

    int atCount = email.count('@');
    if (atCount != 1) {
        return false;
    }

    int atIndex = email.indexOf('@');
    QString username = email.left(atIndex);
    QString domain = email.mid(atIndex + 1);

    if (username.isEmpty() || domain.isEmpty()) {
        return false;
    }

    if (domain.indexOf('.') == -1) {
        return false;
    }

    QSqlQuery query;

    query.prepare("Insert Into ELEVE(MATRICULE,NOM,PRENOM,DATE_NAISSANCE,EMAIL,SEXE) Values(:matricule,:nom,:prenom,:date,:email,:sexe);");
    query.bindValue(":matricule",this->matricule);
    query.bindValue(":nom",this->nom);
    query.bindValue(":prenom",this->prenom);
    query.bindValue(":date",this->dateNaissance);
    query.bindValue(":email",this->email);
    query.bindValue(":sexe",this->sexe);

    return query.exec();
}

QSqlQueryModel * Eleve::afficher(){

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT MATRICULE,NOM,PRENOM,DATE_NAISSANCE,EMAIL,SEXE FROM eleve");

    return modal;

}

bool Eleve::supprimer(QString matricule){

    QSqlQuery query;

    query.prepare("DELETE FROM eleve WHERE matricule=:matricule");
    query.bindValue(":matricule",matricule);

    return query.exec();
}

bool Eleve::modifier(QString matricule){

    int atCount = email.count('@');
    if (atCount != 1) {
        return false;
    }

    int atIndex = email.indexOf('@');
    QString username = email.left(atIndex);
    QString domain = email.mid(atIndex + 1);

    if (username.isEmpty() || domain.isEmpty()) {
        return false;
    }

    if (domain.indexOf('.') == -1) {
        return false;
    }


    QSqlQuery query;

    query.prepare("UPDATE eleve SET MATRICULE = :matricule ,NOM = :nom ,PRENOM = :prenom ,DATE_NAISSANCE = :date ,EMAIL = :email ,SEXE = :sexe WHERE MATRICULE = :mat") ;
    query.bindValue(":matricule",this->matricule);
    query.bindValue(":nom",this->nom);
    query.bindValue(":prenom",this->prenom);
    query.bindValue(":date",this->dateNaissance);
    query.bindValue(":email",this->email);
    query.bindValue(":sexe",this->sexe);
    query.bindValue(":mat",matricule);
     return  query.exec();
}

QSqlQueryModel* Eleve::rechercher(QString toSearch,QString type){

    QSqlQueryModel * modal=new QSqlQueryModel();

    QString query;

    if(type == "nom") {
        query = "SELECT MATRICULE,NOM,PRENOM,DATE_NAISSANCE,EMAIL FROM ELEVE WHERE nom LIKE '%"+toSearch+"%'";
     }
     else if(type == "prenom"){
        query = "SELECT MATRICULE,NOM,PRENOM,DATE_NAISSANCE,EMAIL FROM ELEVE WHERE prenom LIKE '%"+toSearch+"%'";
     }
     else if(type == "email"){
        query = "SELECT MATRICULE,NOM,PRENOM,DATE_NAISSANCE,EMAIL FROM ELEVE WHERE email LIKE '%"+toSearch+"%'";
    }
    else if(type =="matricule"){
        query = "SELECT MATRICULE,NOM,PRENOM,DATE_NAISSANCE,EMAIL FROM ELEVE WHERE matricule LIKE '%"+toSearch+"%'";
    }

    modal->setQuery(query);

    return modal;
}


QPieSeries* Eleve::statistique(){

    QSqlQuery q1,q2,q3;
    qreal tot=0,c1=0,c2=0;

    q1.prepare("SELECT * FROM ELEVE");
    q1.exec();

    q2.prepare("SELECT * FROM ELEVE WHERE SEXE='M'");
    q2.exec();

    q3.prepare("SELECT * FROM ELEVE WHERE SEXE='F'");
    q3.exec();


    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}


    c1=c1/tot;
    c2=c2/tot;

    QPieSeries *series = new QPieSeries();
    series->append("Garçon",c1);
    series->append("Fille",c2);

    return series;

}

QSqlQueryModel* Eleve::tri(QString type){

    QSqlQueryModel * modal=new QSqlQueryModel();

    QString query;

    modal->setQuery("SELECT MATRICULE,NOM,PRENOM,DATE_NAISSANCE,EMAIL FROM ELEVE ORDER BY "+type);

    return modal;

}

void Eleve::exporterCSV(QString fileName,QSqlQueryModel* model){
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        for (int column = 0; column < model->columnCount(); ++column) {
            stream << model->headerData(column, Qt::Horizontal).toString();
            if (column < model->columnCount() - 1)
                stream << ",";
        }
        stream << "\n";

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int column = 0; column < model->columnCount(); ++column) {
                stream << model->data(model->index(row, column)).toString();
                if (column < model->columnCount() - 1)
                    stream << ",";
            }
            stream << "\n";
        }

        file.close();
    }
}

void Eleve::imprimer(QString matricule,QString nom,QString prenom){

    QTextDocument document;

    document.setPlainText("Attstation de presence \nmatricule : "+matricule+"\nNom : "+nom+"\nprenom : "+prenom+"\nje confirme que cette eleve est inscri dans cette etablissement");

    QPrinter printer;
    printer.setPrinterName("desiered printer name");
    QPrintDialog dialog(&printer);

    if (dialog.exec() == QDialog::Accepted) {
        document.print(&printer);
     }
}

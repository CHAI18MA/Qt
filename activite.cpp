#include "activite.h"

Activite::Activite()
{

}

int Activite::getId() const
{
    return id;
}

void Activite::setId(int value)
{
    id = value;
}

QString Activite::getMatricule() const
{
    return matricule;
}

void Activite::setMatricule(const QString &value)
{
    matricule = value;
}

QString Activite::getTitre() const
{
    return titre;
}

void Activite::setTitre(const QString &value)
{
    titre = value;
}

QString Activite::getType() const
{
    return type;
}

void Activite::setType(const QString &value)
{
    type = value;
}

QDate Activite::getDate_act() const
{
    return date_act;
}

void Activite::setDate_act(const QDate &value)
{
    date_act = value;
}

int Activite::getArchive() const
{
    return archive;
}

void Activite::setArchive(int value)
{
    archive = value;
}


bool Activite::ajouter(){
    QSqlQuery query;

    query.prepare("Insert Into ACTIVITE(MATRICULE,TITRE,TYPE,DATE_ACTIVITE,ARCHIVE) Values(:matricule,:titre,:type,:date,0);");
    query.bindValue(":matricule",this->matricule);
    query.bindValue(":titre",this->titre);
    query.bindValue(":type",this->type);
    query.bindValue(":date",this->date_act);


    return query.exec();
}

QSqlQueryModel * Activite::afficher(int archive){
    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT MATRICULE,TITRE,TYPE,DATE_ACTIVITE FROM activite WHERE ARCHIVE="+QString::number(archive)+";");

    return modal;
}

bool Activite::modifier(QString matricule){
    QSqlQuery query;

    query.prepare("UPDATE activite SET MATRICULE = :matricule ,TITRE = :titre ,TYPE = :type ,DATE_ACTIVITE = :date WHERE MATRICULE = :mat") ;
    query.bindValue(":matricule",this->matricule);
    query.bindValue(":titre",this->titre);
    query.bindValue(":type",this->type);
    query.bindValue(":date",this->date_act);
    query.bindValue(":mat",matricule);

    return  query.exec();
}


bool Activite::supprimer(QString matricule){

    QSqlQuery query;

    query.prepare("DELETE FROM activite WHERE matricule=:matricule");
    query.bindValue(":matricule",matricule);

    return query.exec();
}

QBarSeries* Activite::statistique(){

    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM activite");
    q1.exec();

    q2.prepare("SELECT * FROM activite WHERE type='sportif'");
    q2.exec();

    q3.prepare("SELECT * FROM activite WHERE type='artistique'");
    q3.exec();

    q4.prepare("SELECT * FROM activite WHERE type='cultural'");
    q4.exec();


    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}


    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    QBarSet *set0 = new QBarSet("sportif");
    QBarSet *set1 = new QBarSet("artistique");
    QBarSet *set2 = new QBarSet("cultural");

    // Assign values for each bar
    *set0 << c1;
    *set1 << c2;
    *set2 << c3;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    return series;

}

QSqlQueryModel* Activite::tri(QString type,int archive){

    QSqlQueryModel * modal=new QSqlQueryModel();

    QString query;

    modal->setQuery("SELECT MATRICULE,TITRE,TYPE,DATE_ACTIVITE FROM activite WHERE ARCHIVE = "+QString::number(archive)+" ORDER BY "+type+";");

    return modal;

}

QSqlQueryModel* Activite::rechercher(QString toSearch,QString type,int archive){
    QSqlQueryModel * modal=new QSqlQueryModel();

    QString query;

    if(type == "titre") {
        query = "SELECT MATRICULE,TITRE,TYPE,DATE_ACTIVITE FROM activite WHERE ARCHIVE="+QString::number(archive)+" and titre LIKE '%"+toSearch+"%';";
     }
     else if(type == "type"){
        query = "SELECT MATRICULE,TITRE,TYPE,DATE_ACTIVITE FROM activite WHERE ARCHIVE="+QString::number(archive)+" and type LIKE '%"+toSearch+"%';";
     }
     else if(type =="matricule"){
        query = "SELECT MATRICULE,TITRE,TYPE,DATE_ACTIVITE FROM activite WHERE ARCHIVE="+QString::number(archive)+" and matricule LIKE '%"+toSearch+"%';";
     }

    modal->setQuery(query);

    return modal;
}

void Activite::exporterCSV(QString fileName,QSqlQueryModel* model){
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

QStringList Activite::notifcation()
{
    QSqlQuery s;

    QStringList queryResultArray;

    s.prepare("select titre from Activite WHERE TRUNC(date_activite) = TRUNC(SYSDATE)");
    if (s.exec()) {
        while (s.next()) {
            QString columnData = s.value(0).toString(); // Change 0 to the index of your column
            queryResultArray.append(columnData);
        }
    }

    return queryResultArray;
}

bool Activite::archiver(QString matricule,int archive){
    QSqlQuery query;

    query.prepare("UPDATE activite SET ARCHIVE="+ QString::number(archive)+" WHERE MATRICULE = :mat") ;
    query.bindValue(":mat",matricule);

    return  query.exec();
}

void Activite::sms(int argc, char *argv[]){

    QCoreApplication a(argc, argv);

    QNetworkAccessManager manager;
        QNetworkRequest request(QUrl("https://api.twilio.com/2010-04-01/Accounts/AC132cbb8c69d7e9b460192fa8928e93b6/Messages.json"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QByteArray authenticationHeader = "AC132cbb8c69d7e9b460192fa8928e93b6:1de9060f01c7508d4b3ba60263ba7370";
        request.setRawHeader("Authorization", "Basic " + authenticationHeader.toBase64());


        QUrlQuery postData;
        postData.addQueryItem("To","+21694768664");  // Replace with the recipient's phone number
        postData.addQueryItem("From","+12565884356");  // Replace with your Twilio phone number
        postData.addQueryItem("Body","Hello, world!");  // Replace with the SMS message

        QNetworkReply *reply = manager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            qDebug() << "SMS sent successfully!";

            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "SMS sent successfully!";
            } else {
                qDebug() << "Error sending SMS:" << reply->errorString();
            }
            reply->deleteLater();
            a.quit();
        });
}

#ifndef ACTIVITE_H
#define ACTIVITE_H


#include <QString>
#include <QDate>

#include <QDebug>
#include <QCoreApplication>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QFile>
#include <QTextStream>

QT_CHARTS_USE_NAMESPACE


class Activite
{
public:
    Activite();

    int getId() const;
    void setId(int value);

    QString getMatricule() const;
    void setMatricule(const QString &value);

    QString getTitre() const;
    void setTitre(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QDate getDate_act() const;
    void setDate_act(const QDate &value);

    int getArchive() const;
    void setArchive(int value);

    bool ajouter();
    bool modifier(QString matricule);
    QSqlQueryModel * afficher(int archive);
    bool supprimer(QString matricule);


    QSqlQueryModel* tri(QString type,int archive);
    QSqlQueryModel* rechercher(QString toSearch,QString type,int archive);
    QBarSeries* statistique();
    void exporterCSV(QString fileName,QSqlQueryModel* model);
    
    QStringList notifcation();
    bool archiver(QString matricule,int archive);
    void sms(int argc, char *argv[]);

private:
    int id;
    QString matricule;
    QString titre;
    QString type;
    QDate date_act;
    int archive;

};

#endif // ACTIVITE_H

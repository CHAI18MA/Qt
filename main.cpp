#include "mainw.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "activite.h"
#include "mainwindow.h"

#include <QStackedWidget>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslSocket>
#include <QUrlQuery>
#include <QAuthenticator>
#include <QDebug>

#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /*QNetworkAccessManager manager;
        QNetworkRequest request(QUrl("https://api.twilio.com/2010-04-01/Accounts/AC132cbb8c69d7e9b460192fa8928e93b6/Messages.json"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // Prepare the data to be sent
        QByteArray postData;
            postData.append("To=+1234567890");  // Replace with the recipient's phone number
            postData.append("&From=+0987654321");  // Replace with your Twilio phone number
            postData.append("&Body=Hello, world!");

        // Set up basic authentication
        QByteArray authenticationHeader = "AC132cbb8c69d7e9b460192fa8928e93b6:1de9060f01c7508d4b3ba60263ba7370";
        request.setRawHeader("Authorization", "Basic " + authenticationHeader.toBase64());

        // Send the POST request
        QNetworkReply *reply = manager.post(request, postData);

        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            qDebug() << reply->readAll();
            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "SMS sent successfully!";
                qDebug() << reply->readAll();
            } else {
                qDebug() << "Error sending SMS:" << reply->errorString();
            }
            reply->deleteLater();
            qApp->quit(); // Quit the application when done
        });
*/
    Connection c;
    bool test=c.createconnection();
    /*MainW w;
    w.show();*/

    QStackedWidget stackedWidget;

    MainWindow *m = new MainWindow();
    m->show();


   if(test)
   {
       QMessageBox::information(nullptr, QObject::tr("database is open"),
                   QObject::tr("connection successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}
   else
       QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                   QObject::tr("connection failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);



   return a.exec();
}

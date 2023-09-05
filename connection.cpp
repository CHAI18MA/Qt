#include "connection.h"

Connection::Connection()
{}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_projet2A");
    db.setUserName("esprit");
    db.setPassword("esprit");

    if (db.open())
        return true;
    return false;
}
void Connection::closeconnection(){db.close();}

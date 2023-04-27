#include "server.h"


server::server()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase(drivername));
}

void server::connect(){
    db->setHostName("localhost");
    db->setDatabaseName("Milk_DB");
    db->setUserName("postgres");
    db->setPassword("Maoene");

    if(!db->open())
    {
       msg = new QMessageBox;
       msg->setText("Erreur de connection server");
       msg->show();
    }
}

void server::disconnect()
{
  db->close();
}

server::~server()
{
    delete db;
    qDebug() << "Deleted";
}

#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>


class server
{
public:
    server();
    void connect();
    void disconnect();
    const char *drivername = "QPSQL";
    ~server();

private:
    QSqlDatabase *db;
    QSqlQuery *query;
    QMessageBox *msg;
};

#endif // SERVER_H

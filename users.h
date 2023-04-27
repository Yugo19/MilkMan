#ifndef USERS_H
#define USERS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "server.h"
namespace Ui {
class Users;
}

class Users : public QWidget
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr);
    ~Users();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Users *ui;
    server con;
    QSqlQuery *query;
    QMessageBox *msg = new QMessageBox;
    QMessageBox *msg2 = new QMessageBox;
};

#endif // USERS_H

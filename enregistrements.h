#ifndef ENREGISTREMENTS_H
#define ENREGISTREMENTS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "server.h"

namespace Ui {
class Enregistrements;
}

class Enregistrements : public QWidget
{
    Q_OBJECT

public:
    explicit Enregistrements(QWidget *parent = nullptr);
    ~Enregistrements();
    void load_data();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_data_table_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::Enregistrements *ui;
    server con;
    QSqlQuery *query;
    QSqlQueryModel *modal;
    QMessageBox *msg = new QMessageBox;
    QMessageBox *msg2 = new QMessageBox;
};

#endif // ENREGISTREMENTS_H

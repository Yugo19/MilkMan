#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QWidget>

#include "server.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class Statistiques;
}

class Statistiques : public QWidget
{
    Q_OBJECT

public:
    explicit Statistiques(QWidget *parent = nullptr);
    ~Statistiques();
    void load_stats();
    void load_benefice();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Statistiques *ui;
    server con;
    QSqlQuery *query;
    QMessageBox *msg = new QMessageBox;
    QSqlQueryModel *modal;
};

#endif // STATISTIQUES_H

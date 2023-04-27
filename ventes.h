#ifndef VENTES_H
#define VENTES_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "server.h"
#include <QSqlQueryModel>

namespace Ui {
class Ventes;
}

class Ventes : public QWidget
{
    Q_OBJECT

public:
    explicit Ventes(QWidget *parent = nullptr);
    ~Ventes();
    void load_data();
    void load_product_names();
    void valeur_credit();
    void load_revendeurs();
private slots:
    void on_pushButton_clicked();


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_lineEdit_9_textChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_id_revendeur_textChanged(const QString &arg1);

private:
    Ui::Ventes *ui;
    server con;
    QSqlQuery *query;
    QSqlQuery *query2;
    QMessageBox *msg = new QMessageBox;
    QMessageBox *msg2 = new QMessageBox;
    QSqlQueryModel *modal;
};

#endif // VENTES_H

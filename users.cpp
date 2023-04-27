#include "users.h"
#include "ui_users.h"


Users::Users(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->dateEdit->setVisible(false);

}

Users::~Users()
{
    delete ui;
}

void Users::on_pushButton_clicked()
{
    msg2->setWindowTitle("infos");
    msg2->setText("Voulez vous enregistrer");
    msg2->setStandardButtons(QMessageBox::Yes);
    msg2->addButton(QMessageBox::No);
    msg2->setDefaultButton(QMessageBox::No);

    if(msg2->exec() == QMessageBox::Yes)
    {
        con.connect();
        query = new QSqlQuery;
        query->prepare("insert into revendeurs(nom) values(?)");
        query->addBindValue(ui->lineEdit->text());
        if(query->exec())
        {
            con.disconnect();
            con.connect();
            query = new QSqlQuery;
            query->prepare("insert into credits(credits, credit_payes, date_crd) values(?, ?, ?)");
            query->addBindValue(ui->lineEdit_2->text());
            query->addBindValue(ui->lineEdit_3->text());
            query->addBindValue(ui->dateEdit->date());
            query->exec();
            con.disconnect();

            msg->setText("Enregistrer avec succes");
            msg->show();
            ui->lineEdit->setText("");
        }else{
            msg->setText("Echec d'enregistrement");
            msg->show();
            con.disconnect();

        }

    }

}


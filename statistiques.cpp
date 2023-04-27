#include "statistiques.h"
#include "ui_statistiques.h"
#include <QDate>


Statistiques::Statistiques(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistiques)
{
    ui->setupUi(this);

    setWindowTitle("Statistiques");
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    ui->dateEdit_2->setDate(date);
    ui->dateEdit_2->setVisible(false);
    load_stats();
}

Statistiques::~Statistiques()
{
    delete ui;
}

void Statistiques::on_checkBox_stateChanged(int arg1)
{
   if(ui->checkBox->isChecked())
   {
       ui->dateEdit_2->setVisible(true);
   }else
   {
       ui->dateEdit_2->setVisible(false);
   }
}


void Statistiques::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked()){
        if(ui->lineEdit->text()=="Tout")
        {
            con.connect();
            query = new QSqlQuery;
            query->prepare("select (select sum(Total_Argent) from ventes Where date_op between ? and ?)-(select sum(credits-credit_payes) from credits Where date_crd = ?) as total");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->dateEdit_2->date());
            query->addBindValue(ui->dateEdit_2->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_4->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(Total_Vendu) from ventes where date_op between ? and ?");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->dateEdit_2->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_5->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select (credits-credit_payes) from credits WHERE date_crd =? order by id_credit desc limit 1");
            query->addBindValue(ui->dateEdit_2->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_3->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(valeur) from benefices where date_benef between ? and ?");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->dateEdit_2->date());

            query->exec();
            while (query->next())
            {
                ui->benef->setText(query->value(0).toString());
            }
            con.disconnect();


        }else
        {
            con.connect();
            query = new QSqlQuery;
            query->prepare("select (select sum(Total_Argent) from ventes Where date_op between ? and ? and nom = ?)-(select sum(credits-credit_payes) from credits Where date_crd = ?) as total");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->dateEdit_2->date());
            query->addBindValue(ui->lineEdit->text());
            query->addBindValue(ui->dateEdit_2->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_4->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(Total_Vendu) from ventes where date_op between ? and ? and nom = ?;");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->dateEdit_2->date());
            query->addBindValue(ui->lineEdit->text());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_5->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select (credits-credit_payes) from credits WHERE date_crd =? order by id_credit desc limit 1");
            query->addBindValue(ui->dateEdit_2->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_3->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(valeur) from benefices where date_benef between ? and ? and nom_produits = ?");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->dateEdit_2->date());
            query->addBindValue(ui->lineEdit->text());

            query->exec();
            while (query->next())
            {
                ui->benef->setText(query->value(0).toString());
            }
            con.disconnect();


        }
    }else if(ui->checkBox->isChecked() == false)
    {
        if(ui->lineEdit->text() =="Tout")
        {
            con.connect();
            query = new QSqlQuery;
            query->prepare("select (select sum(Total_Argent) from ventes Where date_op = ?)-(select sum(credits-credit_payes) from credits where date_crd=?) as total");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->dateEdit->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_4->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(Total_Vendu) from ventes where date_op = ?");
            query->addBindValue(ui->dateEdit->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_5->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select (credits - credit_payes) from credits WHERE date_crd =? order by id_credit limit 1");
            query->addBindValue(ui->dateEdit->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_3->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(valeur) from benefices where date_benef = ?");
            query->addBindValue(ui->dateEdit->date());
            query->exec();
            while (query->next())
            {
                ui->benef->setText(query->value(0).toString());
            }
            con.disconnect();

        }else{
            con.connect();
            query = new QSqlQuery;
            query->prepare("select (select sum(Total_Argent) from ventes Where date_op = ? and nom = ?)-(select sum(credits-credit_payes) from credits Where date_crd =?) as total");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->lineEdit->text());
            query->addBindValue(ui->dateEdit->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_4->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(Total_Vendu) from ventes where date_op = ? and nom = ?;");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->lineEdit->text());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_5->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select (credits-credit_payes) from credits WHERE date_crd =? order by id_credit desc limit 1");
            query->addBindValue(ui->dateEdit->date());
            query->exec();
            while (query->next())
            {
                ui->lineEdit_3->setText(query->value(0).toString());
            }
            con.disconnect();

            con.connect();
            query = new QSqlQuery;
            query->prepare("select sum(valeur) from benefices where date_benef = ? and nom_produits = ?");
            query->addBindValue(ui->dateEdit->date());
            query->addBindValue(ui->lineEdit->text());
            query->exec();
            while (query->next())
            {
                ui->benef->setText(query->value(0).toString());
            }
            con.disconnect();

        }
    }
}

void Statistiques::load_stats()
{
    con.connect();
    query = new QSqlQuery;
    query->prepare("select (select sum(Total_Argent) from ventes)-(select sum(credits - credit_payes) from credits) as total");
    query->exec();
    while (query->next())
    {
        ui->lineEdit_2->setText(query->value(0).toString());
    }
    con.disconnect();

    con.connect();
    query = new QSqlQuery;
    query->prepare("select sum(Total_Vendu) from ventes");
    query->exec();
    while (query->next())
    {
        ui->lineEdit_7->setText(query->value(0).toString());
    }
    con.disconnect();

    con.connect();
    query = new QSqlQuery;
    query->prepare("select sum(credits - credit_payes) from credits");
    query->exec();
    while (query->next())
    {
        ui->lineEdit_6->setText(query->value(0).toString());
    }
    con.disconnect();


    con.connect();
    modal = new QSqlQueryModel;
    modal->setQuery("select * from ventes");
    ui->data_table->setModel(modal);
    con.disconnect();

    con.connect();
    query = new QSqlQuery;
    query->prepare("select sum(valeur) from benefices where date_benef = (select CURRENT_DATE)");
    query->exec();
    while (query->next())
    {
        ui->benef->setText(query->value(0).toString());
    }
    con.disconnect();


}


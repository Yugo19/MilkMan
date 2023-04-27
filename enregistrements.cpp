#include "enregistrements.h"
#include "ui_enregistrements.h"

Enregistrements::Enregistrements(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Enregistrements)
{
    ui->setupUi(this);
    load_data();
    setWindowTitle("Enregistrement de produiit");
}

Enregistrements::~Enregistrements()
{
    delete ui;
}

void Enregistrements::on_pushButton_clicked()
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
        query->prepare("insert into produits(nom, prix_unitaire, quantité, commission) values(?, ?, ?, ?)");
        query->addBindValue(ui->lineEdit->text());
        query->addBindValue(ui->lineEdit_2->text());
        query->addBindValue(ui->lineEdit_3->text());
        query->addBindValue(ui->lineEdit_4->text());

        if(query->exec())
        {
            msg->setText("Produit enregistré avec succes");
            msg->show();
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
        }else{
            msg->setText("Echec d'enregistrement");
            msg->show();
        }
        con.disconnect();
    }

}


void Enregistrements::on_pushButton_3_clicked()
{
    con.connect();
    query = new QSqlQuery;
    query->prepare("delete from produits where nom = ? ");
    query->addBindValue(ui->lineEdit->text());
    if(query->exec())
    {
       msg->setText("Produit supprimé avec succes");
       msg->show();
    }


    con.disconnect();
}

void Enregistrements::load_data()
{
    con.connect();
    modal = new QSqlQueryModel;
    modal->setQuery("select * from produits");
    ui->data_table->setModel(modal);
    con.disconnect();

    con.connect();
    modal = new QSqlQueryModel;
    modal->setQuery("select nom, quantité from produits where quantité > 100");
    ui->data_table_2->setModel(modal);
    con.disconnect();

    con.connect();
    modal = new QSqlQueryModel;
    modal->setQuery("select nom, quantité from produits  where quantité BETWEEN 100 and  50;");
    ui->data_table_3->setModel(modal);
    con.disconnect();

    con.connect();
    modal = new QSqlQueryModel;
    modal->setQuery("select nom, quantité from produits where quantité < 30");
    ui->data_table_4->setModel(modal);
    con.disconnect();


}


void Enregistrements::on_data_table_doubleClicked(const QModelIndex &index)
{
   con.connect();
   QString Index = ui->data_table->model()->data(index).toString();
   query = new QSqlQuery;
   query->prepare("select * from produits where Nom ='"+Index+"'");
   query->exec();

   while(query->next())
   {
       ui->lineEdit->setText(query->value(0).toString());
       ui->lineEdit_2->setText(query->value(1).toString());
       ui->lineEdit_3->setText(query->value(2).toString());
       ui->lineEdit_4->setText(query->value(3).toString());
   }

   con.disconnect();
}


void Enregistrements::on_pushButton_2_clicked()
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
        query->prepare("update produits set nom = ?, prix_unitaire = ?, quantité = quantité + ?, commission = ? where nom = ?");
        query->addBindValue(ui->lineEdit->text());
        query->addBindValue(ui->lineEdit_2->text());
        query->addBindValue(ui->lineEdit_3->text().toInt());
        query->addBindValue(ui->lineEdit_4->text());
        query->addBindValue(ui->lineEdit->text());

        if(query->exec())
        {
            msg->setText("Produit modifier");
            msg->show();
        }
        con.disconnect();

        load_data();

    }

}


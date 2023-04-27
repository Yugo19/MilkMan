#include "ventes.h"
#include "ui_ventes.h"
#include <QDate>
#include <QString>
#include <QSqlQueryModel>

Ventes::Ventes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventes)
{
    ui->setupUi(this);
    setWindowTitle("Ventes");
    ui->comboBox->setCurrentText("");
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    load_data();
    ui->lineEdit->setVisible(false);
    ui->lineEdit_14->setVisible(false);
    ui->lineEdit_14->setVisible(false);
    ui->id_revendeur->setVisible(true);
    load_product_names();
    load_revendeurs();

}

Ventes::~Ventes()
{
    delete ui;
}

void Ventes::on_pushButton_clicked()
{
    int commission = ui->commission->text().toInt();
    int total_v = ui->lineEdit_9->text().toInt();
    QString benef = QString::number((commission)*(total_v),'g',100);

    msg2->setWindowTitle("infos");
    msg2->setText("Voulez vous enregistrer");
    msg2->setStandardButtons(QMessageBox::Yes);
    msg2->addButton(QMessageBox::No);
    msg2->setDefaultButton(QMessageBox::No);

    if(msg2->exec() == QMessageBox::Yes)
    {

        con.connect();
        query = new QSqlQuery;
        query->prepare("insert into benefices(nom_produits,valeur,id_revendeur,date_benef) values(?, ?, ?, ?)");
        query->addBindValue(ui->comboBox->currentText());
        query->addBindValue(benef);
        query->addBindValue(ui->id_revendeur->text());
        query->addBindValue(ui->dateEdit->date());
        query->exec();

        con.disconnect();

        con.connect();
        query = new QSqlQuery;
        query->prepare("insert into ventes(nom, Prix_Unitaire, Tours1, Tours2, Tours3, Tours4, Retours, Total_Vendu, Total_Argent, date_op, id_revendeur) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query->addBindValue(ui->comboBox->currentText());
        query->addBindValue(ui->lineEdit_2->text());
        query->addBindValue(ui->lineEdit_3->text());
        query->addBindValue(ui->lineEdit_4->text());
        query->addBindValue(ui->lineEdit_5->text());
        query->addBindValue(ui->lineEdit_6->text());
        query->addBindValue(ui->lineEdit_8->text());
        query->addBindValue(ui->lineEdit_9->text());
        query->addBindValue(ui->lineEdit_7->text());
        query->addBindValue(ui->dateEdit->date());
        query->addBindValue(ui->id_revendeur->text());
        if(query->exec() )
        {
            con.disconnect();
            con.connect();
            query2 = new QSqlQuery;
            query2->prepare("update produits set quantité = quantité -? where nom = ?");
            query2->addBindValue(ui->lineEdit_9->text().toInt());
            query2->addBindValue(ui->comboBox->currentText());
            if(query2->exec())
            {
                con.disconnect();
                msg->setText("Transaction validé");
                msg->show();
                ui->lineEdit_3->setText("0");
                ui->lineEdit_4->setText("0");
                ui->lineEdit_5->setText("0");
                ui->lineEdit_6->setText("0");
                ui->lineEdit_7->setText("0");
                ui->lineEdit_8->setText("0");
                ui->lineEdit_9->setText("0");
            }


        }else
        {
            msg->setText("Erreur: Veuillez vérifier les colonnes a remplir");
            msg->show();
            con.disconnect();
        }


        load_data();

    }


}

void Ventes::load_data()
{

    con.connect();
    modal = new QSqlQueryModel;
    modal->setQuery("select * from ventes where date_op = (select CURRENT_DATE)");
    ui->data_table->setModel(modal);
    con.disconnect();
}

void Ventes::load_product_names()
{
    con.connect();
    query = new QSqlQuery;
    query->prepare("select nom from produits");
    query->exec();
    while(query->next())
    {
        ui->comboBox->addItem(query->value(0).toString());
    }
    con.disconnect();

};

void Ventes::on_comboBox_currentTextChanged(const QString &arg1)
{
    con.connect();
    query = new QSqlQuery;
    query->prepare("select prix_unitaire from produits where nom = ?");
    query->addBindValue(ui->comboBox->currentText());
    query->exec();
    while(query->next())
    {
        ui->lineEdit_2->setText(query->value(0).toString());
    }
    con.disconnect();
    load_product_names();
    load_revendeurs();
}


void Ventes::on_pushButton_2_clicked()
{
    try {

        int prix_unit = ui->lineEdit_2->text().toInt();
        int tours1 = ui->lineEdit_3->text().toInt();
        int tours2 = ui->lineEdit_4->text().toInt();
        int tours3 = ui->lineEdit_5->text().toInt();
        int tours4 = ui->lineEdit_6->text().toInt();
        int retour = ui->lineEdit_8->text().toInt();
        QString total_vendu = QString::number((tours1+tours2+tours3+tours4)-(retour),'g',100);
        QString total_argent = QString::number(((tours1+tours2+tours3+tours4)-(retour))*(prix_unit),'g',100);

        ui->lineEdit_9->setText(total_vendu);
        ui->lineEdit_7->setText(total_argent);


    } catch (...) {
    }

}


void Ventes::on_pushButton_3_clicked()
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
        query->prepare("update credits set credits = ? , credit_payes = ?, date_crd = ? where id_revendeur = ?");
        query->addBindValue(ui->lineEdit_10->text());
        query->addBindValue(ui->lineEdit_11->text());
        query->addBindValue(ui->dateEdit->date());
        query->addBindValue(ui->id_revendeur->text());
        if(query->exec()){
            msg->setText("Ok");
            msg->show();
            ui->lineEdit_11->setText("");
        }

        con.disconnect();
        valeur_credit();
    }

}

void Ventes::valeur_credit()
{
    con.connect();
    query->prepare("Select (credits - credit_payes) from credits where id_revendeur = ? order by id_credit desc limit 1");
    query->addBindValue(ui->id_revendeur->text());
    query->exec();
    while (query->next())
    {
        ui->lineEdit_10->setText(query->value(0).toString());
    }
    con.disconnect();

    con.connect();
    query->prepare("Select credit_payes from credits where id_revendeur = ? order by id_credit desc limit 1");
    query->addBindValue(ui->id_revendeur->text());
    query->exec();
    while (query->next())
    {
        ui->lineEdit->setText(query->value(0).toString());
    }
    con.disconnect();


    con.connect();
    query->prepare("Select credits from credits where id_revendeur = ? order by id_credit desc limit 1");
    query->addBindValue(ui->id_revendeur->text());
    query->exec();
    while (query->next())
    {
        ui->lineEdit_14->setText(query->value(0).toString());
    }
    con.disconnect();

}

void Ventes::on_pushButton_4_clicked()
{
    int restant = ui->lineEdit_14->text().toInt();
    int a_ajouter = ui->lineEdit_12->text().toInt();
    QString nv_restant = QString::number((restant+a_ajouter),'g',100);

    msg2->setWindowTitle("infos");
    msg2->setText("Voulez vous enregistrer");
    msg2->setStandardButtons(QMessageBox::Yes);
    msg2->addButton(QMessageBox::No);
    msg2->setDefaultButton(QMessageBox::No);

    if(msg2->exec() == QMessageBox::Yes)
    {
        con.connect();
        query = new QSqlQuery;
        query->prepare("update credits set credits = ?, credit_payes = ?, date_crd = ? where id_revendeur = ?");
        query->addBindValue(nv_restant);
        query->addBindValue(ui->lineEdit->text());
        query->addBindValue(ui->dateEdit->date());
        query->addBindValue(ui->id_revendeur->text());

        if(query->exec()){
            msg->setText("Ok");
            msg->show();
            ui->lineEdit_12->setText("");
        }

        con.disconnect();
        valeur_credit();

    }

}


void Ventes::on_comboBox_2_currentIndexChanged(int index)
{

}

void Ventes::load_revendeurs()
{
    con.connect();
    query = new QSqlQuery;
    query->prepare("select nom from revendeurs");
    query->exec();
    while (query->next()) {
        ui->comboBox_2->addItem(query->value(0).toString());
    }
    con.disconnect();
}


void Ventes::on_lineEdit_9_textChanged(const QString &arg1)
{
    con.connect();
    query = new QSqlQuery;
    query->prepare("select commission from produits where nom=?");
    query->addBindValue(ui->comboBox->currentText());
    query->exec();
    while (query->next()) {
        ui->commission->setText(query->value(0).toString());
    }
    con.disconnect();
}


void Ventes::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    con.connect();
    query = new QSqlQuery;
    query->prepare("select id_revendeur from revendeurs where nom=?");
    query->addBindValue(ui->comboBox_2->currentText());
    query->exec();
    while (query->next()) {
        ui->id_revendeur->setText(query->value(0).toString());
    }
    con.disconnect();
}


void Ventes::on_id_revendeur_textChanged(const QString &arg1)
{
   valeur_credit();
}


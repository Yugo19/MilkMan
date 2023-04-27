#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <QSqlDatabase>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowTitle("Connection");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    con.connect();
    query = new QSqlQuery;

    query->prepare("select * from users where Nom='"+ui->lineEdit->text()+"' and MotPasse='"+ui->lineEdit_2->text()+"' ");
    query->exec();

    if(query->numRowsAffected() ==1)
    {


        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite))

        {

            qDebug() << "FAILED TO CREATE FILE / FILE DOES NOT EXIST";
            msg= new QMessageBox;
            msg->setText("Erreur {000x1}");
            msg->show();

        }else
        {
            QTextStream stream(&file);
            stream << ui->lineEdit->text();
            stream.flush();
            con.disconnect();
            Mw = new MainMenu;
            Mw->show();
            this->close();
        }
    }else{
        qDebug() << "No query exec";
        QMessageBox *msg = new QMessageBox();
        msg->setText("Erreur veillez réeassyer encore");
        msg->show()  ;
    }

    con.disconnect();
}


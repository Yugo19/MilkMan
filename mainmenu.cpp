#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{
    vw = new Ventes;
    vw->show();
}


void MainMenu::on_pushButton_3_clicked()
{
    uw = new Users;
    uw->show();
}


void MainMenu::on_pushButton_4_clicked()
{
   ew = new Enregistrements;
   ew->show();
}


void MainMenu::on_pushButton_2_clicked()
{
   sw = new Statistiques;
   sw->show();
}


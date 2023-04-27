#include "facture.h"
#include "ui_facture.h"

Facture::Facture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Facture)
{
    ui->setupUi(this);
}

Facture::~Facture()
{
    delete ui;
}

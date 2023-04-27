#ifndef FACTURE_H
#define FACTURE_H

#include <QWidget>

namespace Ui {
class Facture;
}

class Facture : public QWidget
{
    Q_OBJECT

public:
    explicit Facture(QWidget *parent = nullptr);
    ~Facture();

private:
    Ui::Facture *ui;
};

#endif // FACTURE_H

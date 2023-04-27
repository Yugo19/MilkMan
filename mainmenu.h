#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "ventes.h"
#include "enregistrements.h"
#include "statistiques.h"
#include "users.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainMenu *ui;
    Ventes *vw;
    Enregistrements *ew;
    Statistiques *sw;
    Users *uw;
};

#endif // MAINMENU_H

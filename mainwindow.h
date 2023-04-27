#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql/QSqlDatabase>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include "mainmenu.h"
#include "server.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString filename = "user.txt";

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    server con;
    MainMenu *Mw;
    QSqlQuery *query = new QSqlQuery;
    QMessageBox *msg;
};
#endif // MAINWINDOW_H

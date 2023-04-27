#ifndef WELCOM_H
#define WELCOM_H

#include <QWidget>

namespace Ui {
class Welcom;
}

class Welcom : public QWidget
{
    Q_OBJECT

public:
    explicit Welcom(QWidget *parent = nullptr);
    ~Welcom();

private:
    Ui::Welcom *ui;
};

#endif // WELCOM_H

#ifndef MOTO_H
#define MOTO_H

#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>

namespace Ui {
    class Moto;
}

class Moto : public QMainWindow
{
    Q_OBJECT

public:
    explicit Moto(QWidget *parent = 0);
    ~Moto();

private slots:
    bool event(QEvent *event);

private:
    Ui::Moto *ui;
};

#endif // MOTO_H

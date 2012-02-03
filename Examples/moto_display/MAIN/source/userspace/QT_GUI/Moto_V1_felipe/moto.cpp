#include "moto.h"
#include "ui_moto.h"

bool a=false;

Moto::Moto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Moto)
{
    ui->setupUi(this);
}

Moto::~Moto()
{
    delete ui;
}

bool Moto::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_5) {
            if(a)
            {
                ui->stackedWidget->setCurrentIndex(1);
                a=false;
            }
            else
            {
                ui->stackedWidget->setCurrentIndex(0);
                a=true;
            }
            return true;
        }
    }
    return QWidget::event(event);
}



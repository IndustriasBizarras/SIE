#include "dial.h"
#include "ui_dial.h"
#include "manometer.h"

dial::dial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dial)
{
    ui->setupUi(this);
}

dial::~dial()
{
    delete ui;
}

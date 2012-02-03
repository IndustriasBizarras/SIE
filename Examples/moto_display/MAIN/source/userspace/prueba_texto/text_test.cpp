#include "text_test.h"
#include "ui_text_test.h"

text_test::text_test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::text_test)
{
    ui->setupUi(this);
}

text_test::~text_test()
{
    delete ui;
}

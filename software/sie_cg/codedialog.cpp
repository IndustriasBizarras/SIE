#include "codedialog.h"
#include "ui_codedialog.h"

codeDialog::codeDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::codeDialog)
{
    ui->setupUi(this);
}

codeDialog::~codeDialog()
{
    delete ui;
}

void codeDialog::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

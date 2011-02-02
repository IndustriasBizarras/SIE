#include "optionsdialog.h"
#include "ui_optionsdialog.h"

optionsDialog::optionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionsDialog)
{
    ui->setupUi(this);
}

optionsDialog::~optionsDialog()
{
    delete ui;
}

void optionsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

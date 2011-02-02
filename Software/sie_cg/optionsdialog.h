#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class optionsDialog;
}

class optionsDialog : public QDialog {
    Q_OBJECT
public:
    optionsDialog(QWidget *parent = 0);
    ~optionsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::optionsDialog *ui;
};

#endif // OPTIONSDIALOG_H

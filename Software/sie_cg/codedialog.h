#ifndef CODEDIALOG_H
#define CODEDIALOG_H

#include <QMainWindow>

namespace Ui {
    class codeDialog;
}

class codeDialog : public QMainWindow {
    Q_OBJECT
public:
    codeDialog(QWidget *parent = 0);
    ~codeDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::codeDialog *ui;
};

#endif // CODEDIALOG_H

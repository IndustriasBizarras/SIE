#ifndef DIAL_H
#define DIAL_H

#include <QMainWindow>

namespace Ui {
    class dial;
}

class dial : public QMainWindow
{
    Q_OBJECT

public:
    explicit dial(QWidget *parent = 0);
    ~dial();

private:
    Ui::dial *ui;
};

#endif // DIAL_H

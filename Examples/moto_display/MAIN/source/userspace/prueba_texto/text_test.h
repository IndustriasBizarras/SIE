#ifndef TEXT_TEST_H
#define TEXT_TEST_H

#include <QMainWindow>

namespace Ui {
    class text_test;
}

class text_test : public QMainWindow
{
    Q_OBJECT

public:
    explicit text_test(QWidget *parent = 0);
    ~text_test();

private:
    Ui::text_test *ui;
};

#endif // TEXT_TEST_H

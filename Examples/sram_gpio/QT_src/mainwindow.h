#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include "jz47xx_mmap.h"
#include "jz47xx_gpio.h"

#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN 26
#define LED_PORT JZ_GPIO_PORT_C
#define LED_PIN 17




namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    JZ_PIO *initGPIO_LED();
    JZ_REG *initFPGA_RAM();

private:
    Ui::MainWindow *ui;
    JZ_PIO *LED;
    JZ_REG *RAM;
    int iter;
protected:
    void timerEvent(QTimerEvent*);
};

#endif // MAINWINDOW_H

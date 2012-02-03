#ifndef MOTO_V2_H
#define MOTO_V2_H

#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>
#include <QTime>
#include <math.h>
#include <ADCw.h>
#include <QFileSystemModel>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace Ui {
    class moto_v2;
}

class moto_v2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit moto_v2(QWidget *parent = 0);
    ~moto_v2();

private slots:
    bool event(QEvent *event);
    void update_info();
    void update_lights();
    void on_treeView_activated(QModelIndex index);

private:
    Ui::moto_v2 *ui;
    QTimer *timer1;
    QTimer *timer2;
    ADCw *ADC1;
    double rpm_val,speed_val;
    int bat,fuel;
    int cont;
    float val_bat  [20];
    float val_fuel [20];
    int rpm_temp[20];
    void read_ADC(int &,int &);
    QFileSystemModel *music_file;
};

#endif // MOTO_V2_H

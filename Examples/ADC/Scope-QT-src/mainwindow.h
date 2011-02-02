#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ADCw.h"

#define PI      3.14159265
#define VrmsC   0.017
#define VmC     0.4999

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool getSign(int val){if(val<0) return 0; else return 1;}

public slots:
	void updateGraph();

signals:
	void refresh();

private:
    Ui::MainWindow *ui;
	QTimer *timer1;
	ADCw *ADC1;
	bool CHANNEL;

    bool sign1_CH1, sign2_CH1; ;
    bool sign1_CH2, sign2_CH2;
    int  deltaCountCH1, deltaCountCH2;
    int  idxCH1, idxCH2;
    double valCH1[200], valCH2[200];
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QTime>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(refresh()),ui->Graph, SLOT(repaint()));
    ui->Graph->setPointsPerPlot(100);
    ui->Graph->setVoltsPerDiv(819);
    ui->Graph->setNumSig(8);

    timer1 =  new QTimer(this);
    timer1->start(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(updateGraph()));

    /*ADC1 = new ADCw;
    ADC1->testADC();
    ADC1->setBufferLen(800);

    ADC1->setClockDiv(ADC_SPI_CLKDIV_MIN); //Max. speed 99KHz
    ADC1->setMuxChannels(7);*/
    printf("\nTaking 100 samples by channel at Fs=12.37KHz (trigger~100ms)\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGraph()
{
    //JZ_REG * dataADC;

    int tempD, tempIdx=0;

        //dataADC=ADC1->takeSamplesADC(0);
        for(int i=0; i< 800/2; i++)
        {
            //tempD = dataADC[i]&0x0FFF;
            tempD = sin(10*PI*i/200)*0x200+0x200;
            ui->Graph->addPoints(tempIdx,tempD+0x3ff*tempIdx);

            //tempD = (dataADC[i]>>16)&0x0FFF;
            tempD = cos(10*PI*i/200)*0x200+0x200;
            ui->Graph->addPoints(tempIdx+1,tempD+0x3ff*(tempIdx+1));

            tempIdx=(tempIdx+2)%8;
        }


    emit refresh();
}

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
    ui->Graph->setPointsPerPlot(200);
    ui->Graph->setVoltsPerDiv(205);

    timer1 =  new QTimer(this);
    timer1->start(50);
    connect(timer1, SIGNAL(timeout()), this, SLOT(updateGraph()));

    ADC1 = new ADCw;
    ADC1->testADC();
    ADC1->setBufferLen(240);
    ADC1->setClockDiv(ADC_SPI_CLKDIV_MIN); //Max. speed
    ADC1->setMuxChannels(1);
    printf("\nTaking 120 samples by channel at Fs=99KHz (trigger=50ms)\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGraph()
{
    JZ_REG * dataADC;    

    int tempD;
    deltaCountCH1=0; deltaCountCH2=0;
    idxCH1=0; idxCH2=0;

        dataADC=ADC1->takeSamplesADC(0);
        for(int i=0; i< 240/2; i++)
        {
            tempD = dataADC[i]&0x0FFF;
            //tempD = sin(10*PI*i/200)*0x200+0x200;
            ui->Graph->addPoint1(tempD+0x3ff);

            sign2_CH1 = getSign(tempD-0x200);
            if((sign1_CH1!=sign2_CH1) & (i>1))
                deltaCountCH1++;                

            if((deltaCountCH1>0) & (deltaCountCH1<3))
            {                
                valCH1[idxCH1]= tempD-0x200;
                idxCH1 ++;
            }

            sign1_CH1=sign2_CH1;

            tempD = (dataADC[i]>>16)&0x0FFF;
            //tempD = cos(10*PI*i/200)*0x200+0x200;
            ui->Graph->addPoint2(tempD);

            sign2_CH2 = getSign(tempD-0x200);
            if((sign1_CH2!=sign2_CH2) & (i>1))
                deltaCountCH2++;

            if((deltaCountCH2>0) & (deltaCountCH2<3))
            {
                valCH2[idxCH2]= tempD-0x200;
                idxCH2 ++;
            }

            sign1_CH2=sign2_CH2;
        }

        double Vrms=0, Vm=0;        

        for(int i=0; i<idxCH1; i++)
        {
            Vrms += pow(valCH1[i],2)/idxCH1;
            Vm += valCH1[i]/idxCH1;
        }

        if(deltaCountCH1>2)
        {
            Vrms=sqrt(Vrms)+VrmsC;
            Vm=Vm+VmC;
            ui->txtVrmsCH1->setText(QString::number(Vrms));
            ui->txtVmCH1->setText(QString::number(Vm));
        }
        else
        {
            ui->txtVrmsCH1->setText("???");
            ui->txtVmCH1->setText("???");
        }

        Vrms=0; Vm=0;
        for(int i=0; i<idxCH2; i++)
        {
            Vrms += pow(valCH2[i],2)/idxCH2;
            Vm += valCH2[i]/idxCH2;
        }

        if(deltaCountCH2>2)
        {
            Vrms=sqrt(Vrms)+VrmsC;
            Vm=Vm+VmC;
            ui->txtVrmsCH2->setText(QString::number(Vrms));
            ui->txtVmCH2->setText(QString::number(Vm));
        }
        else
        {
            ui->txtVrmsCH2->setText("???");
            ui->txtVmCH2->setText("???");
        }

    emit refresh();
}

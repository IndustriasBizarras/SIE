#include "signaldisplay.h"
#include <QtGui>
#include <QDebug>

SignalDisplay::SignalDisplay(QWidget *&parent):QWidget(parent)
{
    secsPerDiv = 1.0/600.0;
	voltsPerDiv = 20;
    numSig=2;
	setPointsPerPlot(10);
}

void SignalDisplay::setNumSig(int value)
{
    numSig = value;
    setPointsPerPlot(pointsPerPlot);
}

void SignalDisplay::setPointsPerPlot(int value)
{
	pointsPerPlot = value;
    waves = new QPoint *[numSig];
    secsIdx=new int[numSig];
    colorTraces = new QColor[numSig];
    int numT=(255/(numSig+1));
    for(int i=0;i<numSig;i++)
    {
        waves[i] = new QPoint [pointsPerPlot];
        secsIdx[i]=0;
        colorTraces[i]=qRgb(numT*(i%numSig),numT*(i%numSig),numT*(i%numSig));
    }
}

void SignalDisplay::drawGrid(QPainter &p, QColor colorGrid, int x, int y, int w, int h, int nx, int ny){
	p.setPen(colorGrid);
	for (int ix= 0; ix<nx; ix++){
		int x = ix*w/nx;
		p.drawLine(x,0,x,h);
	}
	for (int iy = 0; iy < ny; iy++){
		int y = iy*h/ny;
		p.drawLine(0,y,w,y);
	}
}
void SignalDisplay::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	w = width();
	h = height();
	ox = w;
	oy = h;
	painter.fillRect(0,0,w,h,Qt::white);
	drawGrid(painter, Qt::lightGray,0,0,w,h,5, 10);
    for(int i=0; i<numSig; i++)
    {
        painter.setPen(colorTraces[i]);
        painter.drawPolyline(waves[i],pointsPerPlot);
    }
}

void SignalDisplay::addPoints(int idx, int value)
{
    waves[idx][secsIdx[idx]] = 	QPoint(secsIdx[idx]*w/10/60.0/pointsPerPlot/secsPerDiv+w/(2*pointsPerPlot), \
                        oy-value*h/voltsPerDiv/10);
    secsIdx[idx] = (secsIdx[idx]+1) % pointsPerPlot;
}


//EOF

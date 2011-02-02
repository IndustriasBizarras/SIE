#include "signaldisplay.h"
#include <QtGui>
#include <QDebug>

SignalDisplay::SignalDisplay(QWidget *&parent):QWidget(parent)
{
	colorTrace1 = Qt::blue;
	colorTrace2 = Qt::red;
    secsPerDiv = 1.0/600.0;
	voltsPerDiv = 20;
	setPointsPerPlot(10);
}

void SignalDisplay::setPointsPerPlot(int value)
{
	pointsPerPlot = value;
	wave1 = new QPoint[pointsPerPlot];
	wave2 = new QPoint[pointsPerPlot];
	secsIdx1 =  0; secsIdx2 =  0;
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
	painter.setPen(colorTrace1);
	painter.drawPolyline(wave1,pointsPerPlot);
	painter.setPen(colorTrace2);
	painter.drawPolyline(wave2,pointsPerPlot);
}

void SignalDisplay::addPoint1( int value)
{
	wave1[secsIdx1] = 	QPoint(secsIdx1*w/10/60.0/pointsPerPlot/secsPerDiv+w/(2*pointsPerPlot), \
						oy-value*h/voltsPerDiv/10);
	secsIdx1 = (secsIdx1+1) % pointsPerPlot;
}

void SignalDisplay::addPoint2( int value)
{
	wave2[secsIdx2] = 	QPoint(secsIdx2*w/10/60.0/pointsPerPlot/secsPerDiv+w/(2*pointsPerPlot), \
						oy-value*h/voltsPerDiv/10);
	secsIdx2 = (secsIdx2+1) % pointsPerPlot;
}

//EOF

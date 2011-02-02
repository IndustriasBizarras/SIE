#ifndef SIGNALDISPLAY_H
#define SIGNALDISPLAY_H

#include <QWidget>
#include <cmath>
#include <QtGui>

class SignalDisplay : public QWidget
{
public:
	SignalDisplay(QWidget *&parent);
	void addPoint1( int value);
	void addPoint2( int value);
	void setSecsPerDiv( float value ){ secsPerDiv = fabs(value);}
	void setVoltsPerDiv( float value ){ voltsPerDiv = fabs(value);}
	float getSecsPerDiv(){ return secsPerDiv; }
	void  setPointsPerPlot(int value);
	void setColorTrace1(QColor color){colorTrace1=color;}
	void setColorTrace2(QColor color){colorTrace2=color;}

private:
	void paintEvent(QPaintEvent *event);
	void drawGrid(QPainter &p, QColor colorGrid, int x, int y, int w, int h, int nx, int ny);
	QPoint *wave1, *wave2;
	float voltsPerDiv;
	float secsPerDiv;
	QColor colorTrace1,colorTrace2;
	int secsIdx1, secsIdx2;
	int w, h, ox, oy;
	int pointsPerPlot;
};

#endif // SIGNALDISPLAY_H

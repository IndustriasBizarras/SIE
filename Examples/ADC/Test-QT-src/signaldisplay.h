#ifndef SIGNALDISPLAY_H
#define SIGNALDISPLAY_H

#include <QWidget>
#include <cmath>
#include <QtGui>

class SignalDisplay : public QWidget
{
public:
	SignalDisplay(QWidget *&parent);
    void addPoints(int idx, int value);
	void setSecsPerDiv( float value ){ secsPerDiv = fabs(value);}
	void setVoltsPerDiv( float value ){ voltsPerDiv = fabs(value);}
	float getSecsPerDiv(){ return secsPerDiv; }
	void  setPointsPerPlot(int value);
    void setColorTraces(QColor color, int idx){colorTraces[idx]=color;}
    void setNumSig(int value);

private:
	void paintEvent(QPaintEvent *event);
	void drawGrid(QPainter &p, QColor colorGrid, int x, int y, int w, int h, int nx, int ny);
    QPoint **waves;
	float voltsPerDiv;
	float secsPerDiv;
    QColor *colorTraces;
    int *secsIdx;
	int w, h, ox, oy;
	int pointsPerPlot;
    int numSig;
};

#endif // SIGNALDISPLAY_H

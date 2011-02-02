/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "arrow.h"
#include "lineitem.h"
#include <math.h>

const qreal Pi = 3.14;

Arrow::Arrow( QPointF startP,QPointF endP,
              QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPathItem(parent, scene)
{
    startPoint=startP;
    endPoint=endP;
    arrowSize = 10;
    moving=0;
    //setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //setZValue(0.0);
    myOwnerScene = scene;
    lineItem *newLine= new lineItem(QPointF(0,0),QPointF(0,0),this);
    myOwnerScene->addItem(newLine);
    addLine(newLine);

    updatePosition();       
}

void Arrow::removeLine(lineItem *line)
{
    int index = myLines.indexOf(line);

    if (index != -1){      
        //Adjust the corners
        if(myLines.count()>1)
        {
            if(index==0)
            {
                myCorners.removeAt(0);                                
                myOwnerScene->removeItem(myCLines.at(0));
                myCLines.removeAt(0);
            }
            else if(index>0)
            {
                myCorners.removeAt(index-1);
                myOwnerScene->removeItem(myCLines.at(index-1));
                myCLines.removeAt(index-1);
            }
        }
        myLines.removeAt(index);
    }

    //If lines is empty the arrow is removed
    if (myLines.count()<3)
    {                
        removeLines();
        myOwnerScene->removeItem(this);
    }       
}

void Arrow::removeLines()
{
    foreach (lineItem *line, myLines) {
        scene()->removeItem(line);
        delete line;
    }
    foreach (lineItem *line, myCLines) {
        scene()->removeItem(line);
        delete line;
    }
    if(myOwnerScene->items().indexOf(SECLine)!=-1)
    {
        scene()->removeItem(SECLine);
        delete SECLine;
    }
}

bool Arrow::addLine(lineItem *line)
{
        myLines.append(line);
        return 1;
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + arrowSize*2) / 2.0;

    return QGraphicsPathItem::boundingRect()
           .normalized()
           .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsPathItem::shape();    
    return path;
}

void Arrow::updatePosition()
{    
    QPainterPath myPath;
    myPath.moveTo(startPoint);    
    if(!myCorners.isEmpty())
        foreach(QPointF corner, myCorners){
            myPath.lineTo(corner);    
        }
    myPath.lineTo(endPoint);

    setPath(myPath);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    //Update line positions
    QPen myPen = pen();
    myPen.setColor(myColor);   
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QPointF endPos=endPoint;
    QPointF startPos=startPoint;

    if(myCorners.isEmpty())
    {
        myLines.first()->setLine(QLineF(startPos,endPos));
    }
    else
    {
        myLines.first()->setLine(QLineF(startPos,myCorners.first()));
        for(int i=0; i<myCorners.count()-1;i++)        
          myLines.at(i+1)->setLine(QLineF(myCorners.at(i),myCorners.at(i+1)));
        myLines.last()->setLine(QLineF(myCorners.last(),endPos));
    }

    //Drawing arrow selected
    for(int i=0; i<myLines.count();i++)
    {
        if (isSelected())
        {
            painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine));
            QLineF myLine = myLines.at(i)->line();
            painter->drawLine(myLine);
            foreach (lineItem *line, myLines)  { line->setColor(Qt::gray);}
            foreach (lineItem *line, myCLines) { line->setColor(Qt::gray);}
            if(myOwnerScene->items().indexOf(SECLine)!=-1)
                SECLine->setColor(Qt::gray);
        }
        else
        {
            foreach (lineItem *line, myLines)  { line->setColor(myColor);}
            foreach (lineItem *line, myCLines) { line->setColor(myColor);}
            if(myOwnerScene->items().indexOf(SECLine)!=-1)
                SECLine->setColor(myColor);
        }
    }
    painter->setBrush(Qt::lightGray);
    painter->drawPolygon(this->path().toFillPolygon());
    setSelectedArrows();
}

void Arrow::setSelectedArrows()
{
    bool anySelected = 0;

    foreach(lineItem *line,myLines){ if(line->isSelected())anySelected=1;}
    foreach(lineItem *line,myCLines){ if(line->isSelected())anySelected=1;}
    if(isSelected())    anySelected=1;

    if(anySelected)
        setVisibleCorners(1);
    else
        setVisibleCorners(0);
}

void Arrow::createCorner(QPointF cornerPos, lineItem *inLine)
{
    createCorner(cornerPos,myLines.indexOf(inLine));
}

void Arrow::createCorner(QPointF cornerPos, int index)
{
    if (index != -1)
    {
            myCorners.insert(index,cornerPos);
            lineItem *newLine= new lineItem(cornerPos,cornerPos,this);
            myOwnerScene->addItem(newLine);
            newLine->setZValue(this->zValue());
            addLine(newLine);            
            newLine= new lineItem(cornerPos+QPointF(-0.5,-0.5) ,
                                  cornerPos+QPointF(0.5,0.5),this,6,1);
            myOwnerScene->addItem(newLine);
            newLine->setZValue(this->zValue()+0.1);
            myCLines.insert(index,newLine);
    }
    updatePosition();
}
void Arrow::createFirstCorner()
{
    if(myOwnerScene->items().indexOf(SECLine)==-1)
    {
        SECLine = new lineItem(startPoint+QPointF(-0.5,-0.5) ,
                               startPoint+QPointF(0.5,0.5),this,6,1);
        myOwnerScene->addItem(SECLine);
        SECLine->setVisible(1);
        SECLine->setZValue(this->zValue()+0.1);
    }
    updatePosition();
}

void Arrow::moveCorner(QPointF cornerPos, lineItem *inLine, bool relative)
{
    int index = myCLines.indexOf(inLine);
    if(relative) cornerPos=mapFromItem(inLine,cornerPos);

    if (index != -1)
    {
        myCorners.replace(index,cornerPos);
    }
    else if (inLine == SECLine)
    {
        startPoint=cornerPos;
        endPoint=cornerPos;
    }
    updatePosition();
}

void Arrow::setVisibleCorners(bool visible)
{
    foreach (lineItem *line, myCLines) {
        line->setVisible(visible);
        line->setZValue(2000.0);
    }
    if(myOwnerScene->items().indexOf(SECLine)!=-1)
    {
        SECLine->setVisible(1);
    }
    updatePosition();
}

void Arrow::snapToGrid(QGraphicsSceneMouseEvent *event)
{
    //TODO implement polygon drag
    QPointF diffPos= event->scenePos()-previousPos;
    printf("diff[%f|%f]\n",diffPos.x(),diffPos.y()); fflush(stdout);
    //Update corners:
    for(int i=0; i < myCorners.count();i++)
    {        
        myCLines.at(i)->setLine(QLineF(myCLines.at(i)->line().p1()+diffPos,
                                       myCLines.at(i)->line().p2()+diffPos));
        QPointF itemPos =  myCLines.at(i)->line().p1()+QPointF(0.5,0.5);
        moveCorner(itemPos,myCLines.at(i));
    }
    if(myOwnerScene->items().indexOf(SECLine)!=-1)
    {
        SECLine->setLine(QLineF(SECLine->line().p1()+diffPos,
                                 SECLine->line().p2()+diffPos));
        QPointF itemPos =  SECLine->line().p1()+QPointF(0.5,0.5);
        moveCorner(itemPos,SECLine);
    }
    updatePosition();
}

void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    //if(this->isSelected())
    {
        previousPos = event->scenePos();
        moving=1;
    }
    QGraphicsPathItem::mousePressEvent(event);
}

void Arrow::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(moving && isSelected())
    {
        snapToGrid(event);
        previousPos = event->scenePos();
    }
    moving=0;
    QGraphicsPathItem::mouseReleaseEvent(event);
}

void Arrow::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(moving && isSelected())
    {
        snapToGrid(event);
        previousPos = event->scenePos();
    }
    QGraphicsPathItem::mouseMoveEvent(event);
}

QDomElement  Arrow::toXml(QDomDocument &document) const
{
        QDomElement diagramArrow = document.createElement("Polygon");
        //Point list
        if(!myCorners.isEmpty())
        {            
            QDomElement arrowCorner;
            //start point
            arrowCorner = document.createElement("Point");
            arrowCorner.setAttribute("x",(startPoint-QPointF(500,500)).x());
            arrowCorner.setAttribute("y",(startPoint-QPointF(500,500)).y());
            diagramArrow.appendChild(arrowCorner);
            //corner points
            foreach(QPointF corner, myCorners)
            {
                arrowCorner = document.createElement("Point");
                arrowCorner.setAttribute("x",(corner-QPointF(500,500)).x());
                arrowCorner.setAttribute("y",(corner-QPointF(500,500)).y());
                diagramArrow.appendChild(arrowCorner);
            }            
        }
        return (diagramArrow);
}

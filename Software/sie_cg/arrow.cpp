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
#include "diagramscene.h"
#include <math.h>

const qreal Pi = 3.14;

Arrow::Arrow(DiagramTextItem *startItem, DiagramTextItem *endItem,
         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPathItem(parent, scene)
{
    myStartItem = startItem;
    myEndItem = endItem;
    arrowSize = 5;
    moving=0;
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));    
    myOwnerScene = scene;
    lineItem *newLine= new lineItem(QPointF(0,0),QPointF(0,0),this);
    myOwnerScene->addItem(newLine);
    addLine(newLine);
    //setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void Arrow::removeLine(lineItem *line)
{
    int index = myLines.indexOf(line);
    int cIndex = myCLines.indexOf(line);
    if(cIndex!=-1) index = cIndex; //Prevent segmentation fault

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
    if (myLines.isEmpty())
    {        
        this->startItem()->ownerItem()->removeArrow(this);
        this->endItem()->ownerItem()->removeArrow(this);
        this->myOwnerScene->removeItem(this);
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
    return path;  //FIXME, Arrow heads must to be include
}

void Arrow::updatePosition()
{    
    QPainterPath myPath;
    myPath.moveTo(myStartItem->ownerItem()->pos()+myStartItem->offset()+
                  QPointF(arrowSize,0));
    if(!myCorners.isEmpty())
        foreach(QPointF corner, myCorners){
            myPath.lineTo(corner);
        }
    myPath.lineTo(myEndItem->ownerItem()->pos()+myEndItem->offset()-
                  QPointF(arrowSize,0));

    setPath(myPath);

}
//! [3]

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    QPen myPen = pen();
    myPen.setColor(myColor);   
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QPointF endPos=myEndItem->ownerItem()->pos()+myEndItem->offset()-
                   QPointF(arrowSize,0);  
    QPointF startPos=myStartItem->ownerItem()->pos()+myStartItem->offset()+
                     QPointF(arrowSize,0);

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
        if (isSelected())
        {
            painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine));
            QLineF myLine = myLines.at(i)->line();
            painter->drawLine(myLine);
            foreach (lineItem *line, myLines)  { line->setColor(Qt::gray);}
            foreach (lineItem *line, myCLines) { line->setColor(Qt::gray);}
        }
        else
        {
            foreach (lineItem *line, myLines)  { line->setColor(myColor);}
            foreach (lineItem *line, myCLines) { line->setColor(myColor);}
        }

    //End arrow head
    QPointF arrowP1=QPointF(endPos+QPointF(0,arrowSize));
    QPointF arrowP2=QPointF(endPos+QPointF(0,-arrowSize));

    arrowHeadEnd.clear();
    arrowHeadEnd << endPos+QPointF(arrowSize,0) << arrowP1 << arrowP2;

    painter->drawPolygon(arrowHeadEnd);
    //Start arrow head
    arrowP1=QPointF(startPos+QPointF(-arrowSize,arrowSize));
    arrowP2=QPointF(startPos+QPointF(-arrowSize,-arrowSize));

    arrowHeadStart.clear();
    arrowHeadStart << startPos << arrowP1 << arrowP2;
    painter->drawPolygon(arrowHeadStart);

    //Set visible corners
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
            lineItem *newLine= new lineItem(QPointF(0,0),QPointF(0,0),this);
            myOwnerScene->addItem(newLine);
            newLine->setZValue(this->zValue());
            addLine(newLine);
            newLine= new lineItem(cornerPos+QPointF(-0.5,-0.5) ,
                                  cornerPos+QPointF(0.5,0.5),this,6,1);
            myOwnerScene->addItem(newLine);
            newLine->setZValue(this->zValue()+0.1);
            myCLines.insert(index,newLine);
    }
}

void Arrow::moveCorner(QPointF cornerPos, lineItem *inLine)
{
    int index = myCLines.indexOf(inLine);

    if (index != -1)
    {
            cornerPos=mapFromItem(inLine,cornerPos);
            myCorners.replace(index,cornerPos);
            updatePosition();
    }    
}

void Arrow::setVisibleCorners(bool visible)
{
    foreach (lineItem *line, myCLines) {
        line->setVisible(visible);
    }
}

void Arrow::setSelectedLines(bool sel)
{
    foreach (lineItem *line, myCLines) {
        line->setSelected(sel);
    }
    foreach (lineItem *line, myLines) {
        line->setSelected(sel);
    }
}

QDomElement  Arrow::toXml(QDomDocument &document,
                          QHash<int , DiagramItem *> DiagramsID) const
{
        QDomElement diagramArrow = document.createElement("Arrow");

        //Set attibutes; startItem
        diagramArrow.setAttribute("start-x",startOffset().x());
        diagramArrow.setAttribute("start-y",startOffset().y());
        diagramArrow.setAttribute("start-Owner",
                                  DiagramsID.key(startOwner()));
        diagramArrow.setAttribute("start-ID",this->startItem()->textID());

        //Set attibutes; endItem
        diagramArrow.setAttribute("end-x",endOffset().x());
        diagramArrow.setAttribute("end-y",endOffset().y());
        diagramArrow.setAttribute("end-Owner",
                                  DiagramsID.key(endOwner()));
        diagramArrow.setAttribute("end-ID",this->endItem()->textID());

        diagramArrow.setAttribute("color",myColor.name());

        //Corners list
        int i=0;
        if(!myCorners.isEmpty())
        {
            QDomElement arrowCorners = document.createElement("arrowCorners");
            foreach(QPointF corner, myCorners)
            {
                QDomElement arrowCorner = document.createElement("arrowCorner");
                arrowCorner.setAttribute("x",corner.x());
                arrowCorner.setAttribute("y",corner.y());
                i++;
                arrowCorners.appendChild(arrowCorner);
            }

            diagramArrow.appendChild(arrowCorners);
        }
        return (diagramArrow);
}

void Arrow::snapToGrid(QGraphicsSceneMouseEvent *event)
{
    //TODO implement polygon drag
    QPointF diffPos= event->scenePos()-previousPos;
    //Update corners:
    for(int i=0; i < myCorners.count();i++)
    {
        myCLines.at(i)->setLine(QLineF(myCLines.at(i)->line().p1()+diffPos,
                                       myCLines.at(i)->line().p2()+diffPos));
        QPointF itemPos =  myCLines.at(i)->line().p1()+QPointF(0.5,0.5);
        moveCorner(itemPos,myCLines.at(i));
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
    setSelectedLines(false);
    positionChanged=0;
    qobject_cast<DiagramScene *>(myOwnerScene)->saveUndo();

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

    if(!positionChanged)
        qobject_cast<DiagramScene *>(myOwnerScene)->removeLastUndo();
    else
        qobject_cast<DiagramScene *>(myOwnerScene)->clearRedo();

    QGraphicsPathItem::mouseReleaseEvent(event);
}

void Arrow::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(moving && isSelected())
    {
        snapToGrid(event);
        previousPos = event->scenePos();
        positionChanged=1;
    }
    QGraphicsPathItem::mouseMoveEvent(event);
}

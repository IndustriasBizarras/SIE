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

#include "lineitem.h"
#include "diagramscene.h"
#include <math.h>

lineItem::lineItem(QPointF startPoint, QPointF endItem,  Arrow *ownerArrow,
    int wt, bool movable, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    isMovable=movable;
    if(isMovable)
        setFlag(QGraphicsItem::ItemIsMovable, true);

    setFlag(QGraphicsItem::ItemIsSelectable, true);

    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));    
    setLine(QLineF(startPoint,endItem));
    myOwnerArrow = ownerArrow;
    pWidth=wt;
    moveItem=0;
}

QRectF lineItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath lineItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();    
    return path;
}

void lineItem::updatePos()
{    
    QPointF itemPos = this->line().p1();
    myOwnerArrow->moveCorner(itemPos,this);    
}

void lineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    QPen myPen = pen();
    myPen.setColor(myColor);
    myPen.setWidth(pWidth);
    painter->setPen(myPen);
    painter->setBrush(myColor);

    setLine(line());
        painter->drawLine(line());

        //Drawing arrow selected
        if (isSelected()) {
            painter->setPen(QPen(Qt::gray, pWidth, Qt::SolidLine));
            QLineF myLine = line();
            painter->drawLine(myLine);
        }
}

QVariant lineItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
        positionChanged=1;

    return value;
}

void lineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(!isMovable)
    {
        qobject_cast<DiagramScene *>(myOwnerArrow->myOwnerScene)
                ->saveUndoState();
        myOwnerArrow->createCorner(mouseEvent->pos(),this);
    }
    QGraphicsLineItem::mouseDoubleClickEvent(mouseEvent);
}


void lineItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{    
    positionChanged=0;
    qobject_cast<DiagramScene *>(myOwnerArrow->myOwnerScene)->saveUndo();
    myOwner()->setSelectedLines(false);
    setSelected(true);
    QGraphicsLineItem::mousePressEvent(mouseEvent);
}

void lineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMovable)
    {
        updatePos();
    }
    QGraphicsLineItem::mouseMoveEvent(mouseEvent);
}

void lineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMovable)
    {
        updatePos();
    }
    if(!positionChanged)
        qobject_cast<DiagramScene *>(myOwnerArrow->myOwnerScene)
                ->removeLastUndo();
    else
        qobject_cast<DiagramScene *>(myOwnerArrow->myOwnerScene)
                ->clearRedo();
    QGraphicsLineItem::mouseReleaseEvent(mouseEvent);
}

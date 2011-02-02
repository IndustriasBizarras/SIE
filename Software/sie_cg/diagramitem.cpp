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

#include "diagramitem.h"
#include "diagramscene.h"
#include "arrow.h"
#include "diagramtextitem.h"
#include "lineitem.h"

DiagramItem::DiagramItem(
                            QMenu *contextMenu,
                            QString diagramType,
                            QDomElement *domElement,
                            QGraphicsItem *parent, QGraphicsScene *scene,
                            QPointF position, double zV)
    : QGraphicsPolygonItem(parent, scene)
{
    myDiagramType = diagramType;
    myContextMenu = contextMenu;
    myOwnerScene = scene;
    myDomElement=domElement;
    setPos(position);
    setZValue(zV);
    myColor = Qt::white;

    for (QDomNode node = myDomElement->firstChild() ;
         !node.isNull() ;
         node = node.nextSibling())
    {
        QDomElement element = node.toElement();
        if(element.tagName()=="Polygon")
        {
            //READING POLYGON POINTS
            QList<QPointF> points;
            for (QDomNode node = element.firstChild() ;
                             !node.isNull() ;
                             node = node.nextSibling())
            {
                QDomElement point = node.toElement();
                if(point.tagName()=="Point")
                    points.append(QPointF(
                                  point.attribute("x").toFloat(),
                                  point.attribute("y").toFloat()));
            }
            //CREATING POLYGON
            if(points.count()>0)
                foreach(QPointF p, points)
                    myPolygon << p;

        }
        else if(element.tagName()=="TextItems" && myOwnerScene!=0)
        {
            for (QDomNode node = element.firstChild() ;
                             !node.isNull() ;
                             node = node.nextSibling())
            {
                QDomElement textItemE = node.toElement();
            if(textItemE.tagName()=="TextItem")
            {
                int myStyleIO = textItemE.attribute("myStyleIO").
                                toInt();
                int myID = textItemE.attribute("ID").toInt();
                bool editableItem = textItemE.attribute("editableItem").
                                    toInt();
                QPointF posOffset=
                        QPointF(textItemE.attribute("posOffset-x").
                                toFloat(),
                                -textItemE.attribute("posOffset-y").
                                toFloat());
                QString itemString=textItemE.attribute("text");

                DiagramTextItem * newTextItem =
                 new DiagramTextItem(0,myOwnerScene,editableItem,this,myStyleIO,
                                    myID,itemString,posOffset);
                myOwnerScene->addItem(newTextItem);
                newTextItem->setZValue(zValue());
                addText(newTextItem);
            }

            }
        }
    }

    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
}

bool DiagramItem::setValue(unsigned char ID, QString value)
{    
    foreach(DiagramTextItem *item, textItems)
    {
        if(item->isEditable())
        {
            if(item->textID()==ID)
                item->setPlainText(value);
        }
    }
    return 1;
}

DiagramTextItem *DiagramItem::pointerText(unsigned char ID)
{
    foreach(DiagramTextItem *item, textItems)
    {
            if(item->textID()==ID)
                return item;
    }
    return 0;
}

bool DiagramItem::textIsIO(unsigned char ID)
{
    foreach(DiagramTextItem *item, textItems)
    {
            if(item->textID()==ID)
                if(item->styleIO()!=0)
                    return 1;
    }
    return 0;
}

bool DiagramItem::existText(DiagramTextItem * text)
{
    foreach(DiagramTextItem *item, textItems)
    {
            if(item==text)
                return 1;
    }
    return 0;
}

unsigned char DiagramItem::existArrow(DiagramTextItem *startItem,
                                     DiagramTextItem *endItem)
{
    foreach (Arrow *arrow, arrows) {
        if(arrow->startItem()   == startItem &&
           arrow->endItem()     == endItem)
            return 1; //Already exist
        else if(arrow->endItem()== endItem)
            return 1; //End item (INPOUT) already connected        
    }
    return 0;
}

void DiagramItem::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void DiagramItem::removeArrows()
{
    foreach (Arrow *arrow, arrows) {
        arrow->startItem()->ownerItem()->removeArrow(arrow);
        arrow->endItem()->ownerItem()->removeArrow(arrow);
        arrow->removeLines();
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

void DiagramItem::removeTextItem(DiagramTextItem *textItem)
{
    int index = textItems.indexOf(textItem);

    if (index != -1)
        textItems.removeAt(index);
}

void DiagramItem::removeTextItems()
{
    foreach (DiagramTextItem *textItem, textItems) {
        textItem->ownerItem()->removeTextItem(textItem);
        scene()->removeItem(textItem);
        delete textItem;
    }
}

QPixmap DiagramItem::image() const
{
    QSize mySize=this->boundingRect().size().toSize()*1.4;
    QPixmap pixmap(mySize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    int penWidth;
    if(mySize.width()>mySize.height())
        penWidth = int(mySize.width()/32);
    else
        penWidth = int(mySize.height()/32);

    painter.setPen(QPen(Qt::black, penWidth));
    painter.translate(mySize.width()/2, mySize.height()/2);
    QPolygonF Polygon = myPolygon;
    Polygon = Polygon << Polygon.first(); //Adjust the last segment
    painter.drawPolyline(Polygon);
    //TODO text on icon may be interesting
    return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        positionChanged=1;
    }    
    return value;
}

void DiagramItem::updateTexts()
{
    foreach (DiagramTextItem *texts, textItems) {
        texts->updatePosition();
    }
}

void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    positionChanged=0;
    qobject_cast<DiagramScene *>(myOwnerScene)->saveUndo();
    QGraphicsPolygonItem::mousePressEvent(mouseEvent);
}

void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    updateTexts();
    foreach (Arrow *arrow, arrows) {
        arrow->updatePosition();
    }
    QGraphicsPolygonItem::mouseMoveEvent(mouseEvent);
}

void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    foreach (DiagramTextItem *texts, textItems) {
        texts->updatePosition();
    }
    foreach (Arrow *arrow, arrows) {
        arrow->updatePosition();
    }

    if(!positionChanged)
        qobject_cast<DiagramScene *>(myOwnerScene)->removeLastUndo();
    else
        qobject_cast<DiagramScene *>(myOwnerScene)->clearRedo();

    QGraphicsPolygonItem::mouseReleaseEvent(mouseEvent);
}

QDomElement  DiagramItem::toXml(QDomDocument &document) const
{
        QDomElement diagramItem = document.createElement("DiagramItem");

        //Set attibutes; type and position
        diagramItem.setAttribute("type",diagramType());
        diagramItem.setAttribute("x",pos().x());
        diagramItem.setAttribute("y",pos().y());
        diagramItem.setAttribute("z",zValue());
        diagramItem.setAttribute("color",myColor.name());

        //Lists of values (text on editable labels)
        int i=0;        
        QDomElement diagramValues = document.createElement("diagramValues");
        foreach(DiagramTextItem *item, textItems)
        {
            if(item->isEditable())
            {
                QDomElement diagramValue = document.createElement("diagramValue");
                diagramValue.setAttribute("value", item->toPlainText());
                diagramValue.setAttribute("ID", item->textID());
                i++;
                diagramValues.appendChild(diagramValue);
            }
        }
        diagramItem.appendChild(diagramValues);

        return (diagramItem);
}


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

#include "diagramtextitem.h"
#include "diagramscene.h"

DiagramTextItem::DiagramTextItem(
                    QGraphicsItem *parent, QGraphicsScene *scene,
                    bool editable, int styleIO,
                    unsigned char ID, QString defaultText, QPointF offset)
    : QGraphicsTextItem(parent, scene)
{
    myOwnerScene=scene;
    myStyleIO = styleIO;
    myID=ID;
    editableItem=editable;
    setPlainText(defaultText);
    posOffset=offset;

    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    if(myStyleIO==0xFFF)
        setFlag(QGraphicsItem::ItemIsMovable,false);
    else
        setFlag(QGraphicsItem::ItemIsMovable,true);

    setFlag(QGraphicsItem::ItemIsSelectable,true);
    editorOpened=0;

    updatePosition();
}

void DiagramTextItem::updatePosition()
{
        if(myStyleIO>255)
            setPos(posOffset+QPointF(-boundingRect().width()/2,
                                                -boundingRect().height()/2));
        else if(myStyleIO & 0b10000000)
            setPos(posOffset+QPointF(0,-boundingRect().height()/2));
        else                                //OUT
            setPos(posOffset+QPointF(-boundingRect().width(),
                                                -boundingRect().height()/2));
}

QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    return value;
}

void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    setPlainText(toPlainText().trimmed());
    if(toPlainText()=="") setPlainText("?");    
    setTextInteractionFlags(Qt::NoTextInteraction);

    if(myStyleIO!=0xFFF)
        setFlag(QGraphicsItem::ItemIsMovable,true);

    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    setTextCursor(cursor);
    QGraphicsTextItem::focusOutEvent(event);
    editorOpened=0;

    updatePosition();
}

void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(editableItem)
    {        
        if (textInteractionFlags() == Qt::NoTextInteraction)
            setTextInteractionFlags(Qt::TextEditorInteraction);
        setSelected(1);
        setFocus(Qt::MouseFocusReason);
        setFlag(QGraphicsItem::ItemIsMovable,false);
        editorOpened=1;
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void DiagramTextItem::snapToGrid(QGraphicsSceneMouseEvent *event)
{
    if(myStyleIO!=0xFFF)
        setOffset(event->scenePos());    
}

void DiagramTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(editorOpened==0)
    {
        printf("StyleIO:[%x]",myStyleIO); fflush(stdout);
        snapToGrid(event);
        QGraphicsTextItem::mousePressEvent(event);
    }
}

void DiagramTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(editorOpened==0 && myStyleIO!=0xFFF)
    {
        snapToGrid(event);
        QGraphicsTextItem::mouseReleaseEvent(event);        
    }
}

void DiagramTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(editorOpened==0 && myStyleIO!=0xFFF)
    {
        snapToGrid(event);        
        QGraphicsTextItem::mouseMoveEvent(event);
        updatePosition();
    }
}

QDomElement  DiagramTextItem::toXml(QDomDocument &document) const
{
        QDomElement textItem = document.createElement("TextItem");
        textItem.setAttribute("text",toPlainText());
        if(myStyleIO<256)
        {
            textItem.setAttribute("myStyleIO",myStyleIO);
            textItem.setAttribute("editableItem",0);
        }
        else if (myStyleIO==256)
        {
            textItem.setAttribute("myStyleIO",0);
            textItem.setAttribute("editableItem",0);
        }
        else if (myStyleIO==257)
        {
            textItem.setAttribute("myStyleIO",0);
            textItem.setAttribute("editableItem",1);
        }
        textItem.setAttribute("posOffset-x",
                              QPointF(posOffset-QPointF(500,500)).x());
        textItem.setAttribute("posOffset-y",
                              -QPointF(posOffset-QPointF(500,500)).y());
        return (textItem);
}


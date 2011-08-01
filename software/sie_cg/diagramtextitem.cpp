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

DiagramTextItem::DiagramTextItem(QGraphicsItem *parent, QGraphicsScene *scene,
                 bool editable, DiagramItem *ownerItem, unsigned char styleIO,
                 unsigned char ID, QString defaultText, QPointF offset)
    : QGraphicsTextItem(parent, scene)
{
    myOwnerScene = scene;
    myOwnerItem = ownerItem;
    //currentOwnerItem=0;
    myStyleIO = styleIO;
    myID=ID;
    editableItem=editable;    
    if(myOwnerItem==0)
        setZValue(1000.0);
    else
        setZValue(myOwnerItem->zValue());

    setPlainText(defaultText);
    posOffset=offset;

    if(editable && myOwnerItem==0)
    {
        setFlag(QGraphicsItem::ItemIsMovable,true);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
        setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
    }

    setFlag(QGraphicsItem::ItemIsSelectable,true);
    onlyOneUndo=1;
    editorOpened=0;
    updatePosition();    
}

void DiagramTextItem::updatePosition()
{
        QPointF myOwnerPos;


        if(myOwnerItem!=0)
        {
            setZValue(myOwnerItem->zValue());
            myOwnerPos= myOwnerItem->pos();
        }
        else
        {
            setZValue(1000.0);
            myOwnerPos=pos();
        }

        if(myStyleIO==0)
            setPos(myOwnerPos+posOffset+QPointF(-boundingRect().width()/2,
                                                -boundingRect().height()/2));
        else if(myStyleIO & 0b10000000)
            setPos(myOwnerPos+posOffset+QPointF(0,-boundingRect().height()/2));
        else                                //OUT
            setPos(myOwnerPos+posOffset+QPointF(-boundingRect().width(),
                                                -boundingRect().height()/2));
}

QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
        positionChanged=1;

    return value;
}

void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    if(editableItem)
    {
        if(toPlainText()=="") setPlainText("?");
        if(myOwnerItem!=0) updatePosition();
        //Close editor
        setTextInteractionFlags(Qt::NoTextInteraction);
        QTextCursor cursor = textCursor();
        cursor.clearSelection();
        setTextCursor(cursor);
        QGraphicsTextItem::focusOutEvent(event);
        //Determine undo state
        if(myOwnerItem==0) setFlag(QGraphicsItem::ItemIsMovable,true);
        if(toPlainText()==currentText)
            qobject_cast<DiagramScene*>(myOwnerScene)->removeLastUndo();
        else
            qobject_cast<DiagramScene*>(myOwnerScene)->clearRedo();
        onlyOneUndo=1;
        editorOpened=0;
        //Allow deletions when editor is closed
        qobject_cast<DiagramScene *>(myOwnerScene)->myOwnerWindow
                ->dontDelete =0;
    }
}

void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(editableItem)
    {
        if(onlyOneUndo)
        {
            //Save current state to undo list
            currentText = toPlainText();
            qobject_cast<DiagramScene *>(myOwnerScene)->saveUndo();
            //Open editor
            if (textInteractionFlags() == Qt::NoTextInteraction)
                setTextInteractionFlags(Qt::TextEditorInteraction);                       
            setSelected(1);
            setFocus(Qt::MouseFocusReason);
            setFlag(QGraphicsItem::ItemIsMovable,false);
            editorOpened=1;
            //Prevent deletions when editor is opened
            qobject_cast<DiagramScene *>(myOwnerScene)->myOwnerWindow
                    ->dontDelete = 1;
        }
        doubleClicked=1;        
        onlyOneUndo=0;
    }    
}

void DiagramTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{  
    if (myOwnerItem!=0 && editorOpened==0)
    {
        setSelected(0);
        myOwnerItem->mousePressEvent(event);
    }
    else
    {
        positionChanged=0;
        doubleClicked=0;
        qobject_cast<DiagramScene *>(myOwnerScene)->saveUndo();
        QGraphicsTextItem::mousePressEvent(event);
    }
}

void DiagramTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
        if (myOwnerItem!=0 && editorOpened==0)
        {
            myOwnerItem->mouseReleaseEvent(event);
        }
        else
        {
            if(!doubleClicked)
            {
                if(!positionChanged)
                    qobject_cast<DiagramScene*>(myOwnerScene)->removeLastUndo();
                else
                    qobject_cast<DiagramScene*>(myOwnerScene)->clearRedo();
            }
            QGraphicsTextItem::mouseReleaseEvent(event);
        }
}

void DiagramTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
        if (myOwnerItem!=0 && editorOpened==0)
        {
            myOwnerItem->mouseMoveEvent(event);
        }
        else
            QGraphicsTextItem::mouseMoveEvent(event);
}

QDomElement  DiagramTextItem::toXml(QDomDocument &document) const
{
        QDomElement textItem = document.createElement("TextItem");

        //Set attibutes; Text and Font
        textItem.setAttribute("Text",toPlainText());
        textItem.setAttribute("Family",myFont.family());
        textItem.setAttribute("PointSize",myFont.pointSize());
        textItem.setAttribute("Bold",myFont.bold());
        textItem.setAttribute("Italic",myFont.italic());
        textItem.setAttribute("Underline",myFont.underline());
        textItem.setAttribute("Color",defaultTextColor().name());
        textItem.setAttribute("x",pos().x());
        textItem.setAttribute("y",pos().y());

        return (textItem);
}

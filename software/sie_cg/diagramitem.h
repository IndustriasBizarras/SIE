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

#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QList>
#include <QtXml>
#include <stdio.h>

class Arrow;
class DiagramTextItem;

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;
QT_END_NAMESPACE

class QObject;

class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };

    DiagramItem(QMenu *contextMenu,
                QString diagramType,
                QDomElement *domElement,
                QGraphicsItem *parent = 0, QGraphicsScene *scene = 0,
                QPointF position = QPointF(0,0), double zV=500);

    void removeArrow(Arrow *arrow);
    void removeArrows();
    void addArrow(Arrow *arrow);        

    void addText(DiagramTextItem *externalTextItem)
        { textItems.append(externalTextItem);}

    void removeTextItem(DiagramTextItem *textItem);
    void removeTextItems();

    QString diagramType() const
        { return myDiagramType; }

    QPolygonF polygon() const
        { return myPolygon; }

    QDomElement *getDomElement()
        {return myDomElement;}

    QPixmap image() const;

    int type() const
        { return Type;}        

    QList<DiagramTextItem *> getTextItems() const
        { return textItems;}

    QList<Arrow *> getArrows() const
        { return arrows;}

    unsigned char existArrow(DiagramTextItem *startItem,
                             DiagramTextItem *endItem);

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    QDomElement toXml(QDomDocument &) const;

    bool setValue(unsigned char ioID, QString value);
    DiagramTextItem * pointerText(unsigned char ID);
    bool textIsIO(unsigned char ID);

    void setColor(const QColor &color)
        { myColor=color; setBrush(color); }

    int getID()
        { return myID;}

    void setID(int value)
        { myID=value;}

    bool existText(DiagramTextItem * text);

    QGraphicsScene * getOwnerScene()
        { return myOwnerScene;}

    void updateTexts();

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QGraphicsScene *myOwnerScene;
    QString myDiagramType;
    int myID;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;
    QList<DiagramTextItem *> textItems;    
    DiagramTextItem *textItem;
    QColor myColor;
    QDomElement *myDomElement;
    bool positionChanged;
};

#endif

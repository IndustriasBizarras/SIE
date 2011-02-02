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

#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QDesktopServices>
#include <QtXml>
#include "diagramtextitem.h"
#include "arrow.h"
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QStatusBar;
QT_END_NAMESPACE
class MainWindow;
class Arrow;
class DiagramTextItem;

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { MoveItem , EditPolygon, InsertText };

    DiagramScene(QMenu *itemMenu,  MainWindow *ownerWindow, QObject *parent=0);

    QDomDocument toXmlFormat();
    int fromXmlFormat(QDomDocument xmlDocument);
    void cleanScene();
    void setTextType(int type,QString text){myTextType=type;myTypeString=text;}
    void resetMyPolygon(){myPolygonPath=0;}

    QHash<int,DiagramTextItem*> getTextItemsByID;

    int addTextItem(DiagramTextItem * textItem);
    void removeTextItem(DiagramTextItem * textItem);

    Arrow *myPolygonPath;

    QString createPrototype();

public slots:
    void setMode(Mode mode){myMode=mode;}        

signals:    
    void textInserted(QGraphicsTextItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void drawBackground(QPainter *p, const QRectF &r);

private:
    bool isItemChange(int type);
    void doSnapToGrid(QGraphicsSceneMouseEvent *mouseEvent);
    QMenu *myItemMenu;
    Mode myMode;
    int myTextType;
    QString myTypeString;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;    
    QFont myFont;
    DiagramTextItem *textItem;
    DiagramTextItem *TitleText;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
    bool snapToGrid;
    short int myGrid;
    int myCorners;
    QHash<int,DiagramTextItem*> textItemsByID;
    MainWindow *myOwnerWindow;
};

#endif

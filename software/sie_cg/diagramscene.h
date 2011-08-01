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
#include "diagramitem.h"
#include "diagramtextitem.h"
#include "mainwindow.h"

class MainWindow;
class DiagramTextItem;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    DiagramScene(QMenu *itemMenu, MainWindow *ownerWindow,
                 QObject *parent = 0);

    QFont font() const
        { return myFont; }
    QColor textColor() const
        { return myTextColor; }
    QColor itemColor() const
        { return myItemColor; }
    QColor lineColor() const
        { return myLineColor; }
    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(QFont font);
    void setDawGrid(bool value) {drawGrid=value;}

    QDomDocument toXmlFormat();
    int fromXmlFormat(QDomDocument xmlDocument);
    void cleanScene();

    QHash<int , DiagramItem *> getDiagramsID ()
        { return DiagramsID;}

    QStringList getLibList(){return libraryList;}
    void setLibList(QStringList list)
        {libraryList=list;}

    void setDomElementsByName(QHash<QString , QDomElement*> *hash)
        {domElementsByName=hash;}

    void setButtonIdByName(QHash<QString , int> hash)
        {buttonIdByName=hash;}

    int addDiagramItem(DiagramItem * item);
    void removeDiagramItem(DiagramItem * item);

    MainWindow *myOwnerWindow;

    void saveUndoState();
    void saveUndo();
    void removeLastUndo();
    void clearRedo();

public slots:
    void setMode(Mode mode);
    void setItemType(QString type);

signals:
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void drawBackground(QPainter *p, const QRectF &r);

private:
    bool isItemChange(int type);
    void doSnapToGrid(QGraphicsSceneMouseEvent *mouseEvent);
    QString myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    DiagramTextItem *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
    bool snapToGrid;
    bool drawGrid;
    short int myGrid;
    QStringList libraryList;
    QHash<QString , QDomElement*> *domElementsByName;
    QHash<QString , int> buttonIdByName;
    QHash<int , DiagramItem *> DiagramsID;    
};

#endif

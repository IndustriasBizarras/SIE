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
#include <QHash>
#include "diagramscene.h"
#include "arrow.h"

DiagramScene::DiagramScene(QMenu *itemMenu, MainWindow *ownerWindow,
                           QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = "";
    line = 0;
    textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
    snapToGrid=1;
    myGrid=10;
    drawGrid=0;
    myOwnerWindow=ownerWindow;
}

void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;

    //Lists of items
    QList<Arrow *> Arrows;
    QList<lineItem *> lineItems;
    foreach(QGraphicsItem *item, selectedItems()){
        if(item->type() == lineItem::Type)
            lineItems.append(qgraphicsitem_cast<lineItem *>(item));
        else if(item->type() == Arrow::Type)
            Arrows.append(qgraphicsitem_cast<Arrow *>(item));
    }

    foreach(Arrow *arrow, Arrows){
        saveUndoState();
        arrow->setColor(myLineColor);
    }

    foreach(lineItem *line, lineItems){
        saveUndoState();
        line->myOwner()->setColor(myLineColor);
    }

    update();
}

void DiagramScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    //Lists of items
    QList<DiagramTextItem *> textItems;
    foreach(QGraphicsItem *item, selectedItems()){
        if(item->type() == DiagramTextItem::Type)
            textItems.append(qgraphicsitem_cast<DiagramTextItem *>(item));
    }

    foreach(DiagramTextItem *textItem, textItems){
        if(textItem->ownerItem()==0)
        {
            saveUndoState();
            textItem->setDefaultTextColor(myTextColor);
        }
    }

    update();
}

void DiagramScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    //Lists of items
    QList<DiagramItem *> items;
    foreach(QGraphicsItem *item, selectedItems()){
        if(item->type() == DiagramItem::Type)
            items.append(qgraphicsitem_cast<DiagramItem *>(item));
    }

    foreach(DiagramItem *item, items){
        saveUndoState();
        item->setColor(myItemColor);
    }

}

void DiagramScene::setFont(QFont font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        saveUndoState();
        DiagramTextItem *item =
            qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
            item->setFontt(myFont);
    }
}

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(QString type)
{
    myItemType = type;
}

void DiagramScene::saveUndoState()
{
    saveUndo();
    clearRedo();
    fflush(stdout);
}
void DiagramScene::saveUndo()
{
    myOwnerWindow->undoList.append(toXmlFormat());
    fflush(stdout);
}

void DiagramScene::removeLastUndo()
{
    if(!myOwnerWindow->undoList.isEmpty())
        myOwnerWindow->undoList.removeLast();
    fflush(stdout);
}

void DiagramScene::clearRedo()
{
    myOwnerWindow->redoList.clear();    
    fflush(stdout);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);

    if (mouseEvent->button() != Qt::LeftButton)
        return;

    foreach (QGraphicsItem *item, this->items(mouseEvent->scenePos())) {
        if (item->type() == DiagramTextItem::Type)
        {
            myOwnerWindow->setFontSettings(qgraphicsitem_cast<DiagramTextItem *>
                                           (item)->font());
        }
    }

    DiagramItem *item;
    int addResult=0;

    switch (myMode) {
        case InsertItem:
            saveUndoState();
            item = new DiagramItem(myItemMenu,myItemType,
                                   domElementsByName->value(myItemType),0,this);
            addResult=addDiagramItem(item);
            if(addResult!=-1)
            {
                item->setColor(myItemColor);                
                item->setPos(mouseEvent->scenePos());
                item->setID(addResult);
                item->updateTexts();
                addItem(item);
            }
            else
            {
                delete(item);
                QMessageBox::warning(0,"Full","The diagram can only have "
                                     "5000 blocks. <b>You are crasy?</b>");
            }
            emit itemInserted(item);
            break;
        case InsertLine:            
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            line->setZValue(1000.0);            
            snapToGrid=0;
            addItem(line);                        
            break;
        case InsertText:
            saveUndoState();
            textItem = new DiagramTextItem(0,this);
            textItem->setFontt(myFont);
            textItem->setZValue(1000.0);      
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            addItem(textItem);
            emit textInserted(textItem);
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::doSnapToGrid(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(snapToGrid){
        mouseEvent->setScenePos(QPointF(
                                round(mouseEvent->scenePos().x()/myGrid)*myGrid,
                                round(mouseEvent->scenePos().y()/myGrid)*myGrid
                                ));
    }
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }   
    QPointF mousePos = mouseEvent->scenePos();
    QString barMesg= QString("X[%1] Y[%2]").arg(QString::number(mousePos.x()))
                                           .arg(QString::number(mousePos.y()));

    foreach (QGraphicsItem *item, items(mousePos)) {
        if (item->type() == DiagramItem::Type) {
             barMesg+= tr(" ** Over diagram block with ID[") +
                       QString::number(qgraphicsitem_cast<DiagramItem *>
                                  (item)->getID()) + tr("]");
        }
    }
    myOwnerWindow->statusBar->showMessage(barMesg);
}

void DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
        //Diferents items and valid type
        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == DiagramTextItem::Type &&
            endItems.first()->type() == DiagramTextItem::Type &&
            startItems.first() != endItems.first())
        {
            DiagramTextItem *startItem_ =
                qgraphicsitem_cast<DiagramTextItem *>(startItems.first());
            DiagramTextItem *endItem_ =
                qgraphicsitem_cast<DiagramTextItem *>(endItems.first());

            //Real first and  real end item
            DiagramTextItem *startItem = startItem_;
            DiagramTextItem *endItem = endItem_;
            if(startItem_->styleIO()>>7)
            {
                startItem = endItem_;
                endItem = startItem_;
            }

            //Inputs to outputs and diferent owner
            if(startItem->styleIO()>0                                   &&
               endItem->styleIO()>0                                     &&
              (startItem->styleIO()>>7 != endItem->styleIO()>>7)        &&
              (startItem->ownerItem()  != endItem->ownerItem())         &&
               !endItem->ownerItem()->existArrow(startItem,endItem)
              )
            {
                saveUndoState();
                Arrow *arrow = new Arrow(startItem, endItem,0,this);
                arrow->setColor(myLineColor);
                startItem->ownerItem()->addArrow(arrow);
                endItem->ownerItem()->addArrow(arrow);
                arrow->setZValue(0.0);
                addItem(arrow);
                arrow->updatePosition();
            }
        }
    }
    line = 0;
    snapToGrid=1;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}

int DiagramScene::addDiagramItem(DiagramItem * item)
{
    for(int i=0; i<5000; i++)
    {
        QHash<int,DiagramItem *>::iterator iter= DiagramsID.find(i);
        if(iter==DiagramsID.end())
        {
            DiagramsID.insert(i,item);
            return i;
        }
    }
    return -1;
}

void DiagramScene::removeDiagramItem(DiagramItem * item)
{
    DiagramsID.remove(DiagramsID.key(item));
}

QDomDocument DiagramScene::toXmlFormat()
{
    QDomDocument document;
    QDomComment initialComments=document.createComment(
        "\nFile for SIE Code Generator.\n"
        "**WARNING**If you are going to edit this file note that:\n"
        "In order to segmentation faults prevention the load process \n"
        "is started loading the libraries, then items and finally arrows.\n"
        "Arrows depend of items, and items depend of libraries!!!!\n");
    document.appendChild(initialComments);
    QDomElement diagram = document.createElement("Diagram");
    document.appendChild(diagram);

    //Lists of items
    QList<DiagramItem *> Items;
    QList<Arrow *> Arrows;   
    QList<DiagramTextItem *> TextItems;
    foreach(QGraphicsItem *item, items())
    {
        if(item->type() == DiagramItem::Type)
            Items.append(qgraphicsitem_cast<DiagramItem *>(item));
        else if(item->type() == Arrow::Type)
            Arrows.append(qgraphicsitem_cast<Arrow *>(item));
        else if(item->type() == DiagramTextItem::Type)
            if(qgraphicsitem_cast<DiagramTextItem *>(item)->ownerItem() == 0)
                TextItems.append(qgraphicsitem_cast<DiagramTextItem *>(item));
    }
    //Create the XML structure
    QDomElement element;

    //Save libraries
    if(!libraryList.isEmpty())
    {
        QDomElement libraries = document.createElement("Libraries");
        foreach(QString lib, libraryList)
        {
            element =  document.createElement("Library");
            element.setAttribute("Dir",lib);
            libraries.appendChild(element);
        }
        diagram.appendChild(libraries);

    }

    //Save options
        QDomElement options = document.createElement("Options");
        options.setAttribute("templateDir", myOwnerWindow->templateDir);
        options.setAttribute("templateFile", myOwnerWindow->templateFile);
        options.setAttribute("makeFile", myOwnerWindow->makeFile);
        options.setAttribute("workDir",  myOwnerWindow->workDir);
        options.setAttribute("executableFile",  myOwnerWindow->executableFile);
        options.setAttribute("mipsToolChainDir",  myOwnerWindow->mipsToolChainDir);
        options.setAttribute("mipsToolChain",  myOwnerWindow->mipsToolChain);
        options.setAttribute("sieWorkDir",  myOwnerWindow->sieWorkDir);
        options.setAttribute("fpgaFile",  myOwnerWindow->fpgaFile);
        options.setAttribute("sieIP",  myOwnerWindow->sieIP);
        options.setAttribute("configApp", myOwnerWindow->configApp);
        diagram.appendChild(options);

    //Save items
    if(!Items.isEmpty())
    {
        QDomElement diagramItems = document.createElement("DiagramItems");
        foreach(DiagramItem *item, Items)
        {
            element = item->toXml(document);
            element.setAttribute("ID",item->getID()); //save index
            diagramItems.appendChild(element);
        }
        diagram.appendChild(diagramItems);
    }

    //Save arrows
    if(!Arrows.isEmpty())
    {
        QDomElement arrowItems = document.createElement("Arrows");
        foreach(Arrow *item, Arrows)
        {
            element = item->toXml(document,DiagramsID);
            element.setAttribute("ID",Arrows.indexOf(item)); //save index            
            arrowItems.appendChild(element);
        }
        diagram.appendChild(arrowItems);
    }

    //Save text items
    if(!TextItems.isEmpty())
    {
        QDomElement textItems = document.createElement("TextItems");
        foreach(DiagramTextItem *item, TextItems)
        {
            element = item->toXml(document);
            textItems.appendChild(element);
        }
        diagram.appendChild(textItems);
    }

    return(document);
}

int DiagramScene::fromXmlFormat(QDomDocument document)
{
    DiagramsID.clear();
    //Read diagrams TODO: in future... add multi projects functionality
    QDomNodeList diagrams = document.elementsByTagName("Diagram");
    if(!diagrams.at(0).isElement())
        return 0;
    //Load the first diagram in the document
    QDomElement diagram = diagrams.at(0).toElement();
    //In order to segmentation faults prevention the load process
    //is started loading the libraries, then items and finally arrows.
    //Arrows depend of items, and items depend of libraries!!!
    //TODO: rewrite this process for reading in the order specified
    for (QDomNode node = diagram.firstChild() ;
         !node.isNull() ;
         node = node.nextSibling())
    {                
        QDomElement element = node.toElement();
        if(element.tagName()=="Options")
        {
            myOwnerWindow->templateDir= element.attribute("templateDir");
            myOwnerWindow->templateFile= element.attribute("templateFile");
            myOwnerWindow->makeFile= element.attribute("makeFile");
            myOwnerWindow->workDir= element.attribute("workDir");
            myOwnerWindow->executableFile= element.attribute("executableFile");
            myOwnerWindow->mipsToolChainDir= element.attribute("mipsToolChainDir");
            myOwnerWindow->mipsToolChain= element.attribute("mipsToolChain");
            myOwnerWindow->sieWorkDir= element.attribute("sieWorkDir");
            myOwnerWindow->fpgaFile= element.attribute("fpgaFile");
            myOwnerWindow->sieIP= element.attribute("sieIP");
            myOwnerWindow->configApp= element.attribute("configApp");
        }
        else if(element.tagName()=="Libraries")
        {
            libraryList.clear();
            for (QDomNode node = element.firstChild() ;
                !node.isNull() ;
                node = node.nextSibling())
            {
                //Load library directory
                QDomElement Library = node.toElement();
                if(Library.tagName()!="Library")
                    return 0;
                libraryList.append(Library.attribute("Dir"));                
            }
            myOwnerWindow->updateLibraries();
        }
        else if(element.tagName()=="DiagramItems") //Load diagram items
        {
            for (QDomNode node = element.firstChild() ;
                 !node.isNull() ;
                 node = node.nextSibling())
            {                
                //Load diagram item and add to scene
                QDomElement diagramItem = node.toElement();
                if(diagramItem.tagName()!="DiagramItem")
                    return 0;

                QPointF position = QPointF(diagramItem.attribute("x").toFloat(),
                                          diagramItem.attribute("y").toFloat());
                //PREVENT Segmentation faults:
                if(!domElementsByName->contains(
                   diagramItem.attribute("type")))
                {
                    QMessageBox::critical(0,"Error",QObject::tr(
                                          "Diagram can't be loaded, because the"
                                          " library for block [") +
                                          diagramItem.attribute("type") +tr(
                                          "] can't be found."));
                    return 0;
                }

                DiagramItem *newItem=new DiagramItem(
                        myItemMenu,
                        diagramItem.attribute("type"),
                        domElementsByName->value(diagramItem.attribute("type")),
                        0,this, position,
                        diagramItem.attribute("z").toDouble());

                newItem->setColor(QColor(diagramItem.attribute("color")));
                int itemID=diagramItem.attribute("ID").toInt();
                newItem->setID(itemID);                            

                addItem(newItem);                                
                for (QDomNode node = diagramItem.firstChild() ;
                     !node.isNull() ;
                     node = node.nextSibling())
                {
                    //Load diagram text values and set on diagram item
                    QDomElement diagramValues = node.toElement();
                    if(diagramValues.tagName()!="diagramValues")
                        return 0;

                    for (QDomNode node = diagramValues.firstChild() ;
                         !node.isNull() ;
                         node = node.nextSibling())
                    {
                        QDomElement diagramValue = node.toElement();
                        if(diagramValue.tagName()!="diagramValue")
                            return 0;
                        newItem->setValue(diagramValue.attribute("ID").toInt(),
                                          diagramValue.attribute("value"));
                    }                                       
                }
                newItem->updateTexts();
                if(DiagramsID.find(itemID)!=DiagramsID.end())
                {
                    int result=addDiagramItem(newItem);
                    QMessageBox::warning(0,"ID Problems",
                        tr("Block with ID[")+QString::number(itemID)+
                        tr("] already exists, this will be reasigned to [")+
                        QString::number(result)+
                        tr("] for prevent problems."));
                    newItem->setID(result);
                }
                else
                    DiagramsID.insert(itemID,newItem);
            }
        }
        else if(element.tagName()=="Arrows")
        {

            for (QDomNode node = element.firstChild() ;
                 !node.isNull() ;
                 node = node.nextSibling())
            {
                //Load arrow item and add to scene
                QDomElement arrow = node.toElement();
                if(arrow.tagName()!="Arrow")
                    return 0;

                DiagramTextItem *startItem=
                        DiagramsID.value(arrow.attribute("start-Owner").toInt())
                        ->pointerText(arrow.attribute("start-ID").toInt());
                bool startIsIO =
                        DiagramsID.value(arrow.attribute("start-Owner").toInt())
                        ->textIsIO(arrow.attribute("start-ID").toInt());
                DiagramTextItem *endItem=
                        DiagramsID.value(arrow.attribute("end-Owner").toInt())
                        ->pointerText(arrow.attribute("end-ID").toInt());
                bool endIsIO =
                        DiagramsID.value(arrow.attribute("end-Owner").toInt())
                        ->textIsIO(arrow.attribute("end-ID").toInt());

                if(!startIsIO||!endIsIO)
                {
                    QMessageBox::warning(0,"Arrow can't be loaded.",
                                     tr("An arrow can not be loaded because ")+
                                     tr("will be connected to a label")+
                                     tr(" that isn't an Input/Output type. ")+
                                     tr("Probable cause may be that the start")+
                                     tr(" or end block has been modified."));
                }
                else if(startItem==0 || endItem==0)
                {
                    QMessageBox::warning(0,"Arrow can't be loaded",
                                     tr("An arrow can not be loaded because ")+
                                     tr("her IO label ID could not be found. ")+
                                     tr("Probable cause may be that the start")+
                                     tr(" or end block has been modified."));
                }
                else
                {
                    Arrow *newArrow = new Arrow(startItem, endItem,0,this);
                    newArrow->setColor(QColor(arrow.attribute("color")));
                    startItem->ownerItem()->addArrow(newArrow);
                    endItem->ownerItem()->addArrow(newArrow);
                    newArrow->setZValue(0.0);
                    addItem(newArrow);
                    newArrow->updatePosition();

                    for (QDomNode node = arrow.firstChild() ;
                         !node.isNull() ;
                         node = node.nextSibling())
                    {
                        //Load diagram text values and set on diagram item
                        QDomElement arrowCorners = node.toElement();
                        if(arrowCorners.tagName()!="arrowCorners")
                            return 0;
                        int i=0;
                        for (QDomNode node = arrowCorners.firstChild() ;
                             !node.isNull() ;
                             node = node.nextSibling())
                        {
                            QDomElement arrowCorner = node.toElement();
                            if(arrowCorner.tagName()!="arrowCorner")
                                return 0;

                            QPointF cornerPos =
                                    QPointF(arrowCorner.attribute("x").toFloat(),
                                            arrowCorner.attribute("y").toFloat());

                            newArrow->createCorner(cornerPos,++i);
                        }
                    }
                }
            }
        }
        else if(element.tagName()=="TextItems")
        {
            for (QDomNode node = element.firstChild() ;
                !node.isNull() ;
                node = node.nextSibling())
            {
                //Load library directory
                QDomElement textItem = node.toElement();
                if(textItem.tagName()!="TextItem")
                    return 0;

                QFont textFont;
                textFont.setFamily(textItem.attribute("Family"));
                textFont.setPointSize(textItem.attribute("PointSize").toInt());
                textFont.setBold(textItem.attribute("Bold").toInt());
                textFont.setItalic(textItem.attribute("Italic").toInt());
                textFont.setUnderline(textItem.attribute("Underline").toInt());

                DiagramTextItem *newText = new DiagramTextItem(0,this);
                newText->setFontt(textFont);                
                newText->setDefaultTextColor(
                        QColor(textItem.attribute("Color")));
                newText->setPos(QPointF(
                        textItem.attribute("x").toFloat(),
                        textItem.attribute("y").toFloat()));
                newText->setPlainText(textItem.attribute("Text"));
                addItem(newText);
            }
        }        
    }

    return 1;
}

void DiagramScene::cleanScene()
{
    //Lists of items
    QList<DiagramItem *> Items;
    QList<Arrow *> Arrows;
    foreach(QGraphicsItem *item, items())
    {
        if(item->type() == DiagramItem::Type)
            Items.append(qgraphicsitem_cast<DiagramItem *>(item));
        else if(item->type() == Arrow::Type)
            Arrows.append(qgraphicsitem_cast<Arrow *>(item));
    }
    //Delete only DiagramItems: When a diagramitem is deleted his arrows and
    //textitems have to be deleted too, so if we delete only diagramitems then
    //we are deleting all items in the scene. This is in order to prevent
    //segmentation faults.
    foreach(DiagramItem *item, Items)
    {
        item->removeArrows();
        item->removeTextItems();
        removeItem(item);
        delete(item);
    }
    //Delete the text items without parents
    foreach(QGraphicsItem *item, items())
    {
        removeItem(item);
        delete(item);
    }
    this->clear();
    DiagramsID.clear();    
}

void DiagramScene::drawBackground(QPainter *p, const QRectF &r)
{
    //TODO: add a button for activate/deactivate the grid.

    QGraphicsScene::drawBackground(p,r);
    if(drawGrid)
    {
        p -> save();

        p -> setRenderHint(QPainter::Antialiasing, false);
        p -> setRenderHint(QPainter::TextAntialiasing, true);
        p -> setRenderHint(QPainter::SmoothPixmapTransform, false);

        p -> setPen(Qt::NoPen);
        p -> setBrush(Qt::white);
        p -> drawRect(r);


        p -> setPen(Qt::black);
        p -> setBrush(Qt::NoBrush);
        qreal limite_x = r.x() + r.width();
        qreal limite_y = r.y() + r.height();

        int g_x = (int)ceil(r.x());
        while (g_x % myGrid) ++ g_x;
        int g_y = (int)ceil(r.y());
        while (g_y % myGrid) ++ g_y;

        QPolygon points;
        for (int gx = g_x ; gx < limite_x ; gx += myGrid) {
            for (int gy = g_y ; gy < limite_y ; gy += myGrid) {
                points << QPoint(gx, gy);
            }
        }
        p -> drawPoints(points);
        p -> restore();
    }
}

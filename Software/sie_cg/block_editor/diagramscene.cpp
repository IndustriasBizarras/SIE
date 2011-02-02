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

DiagramScene::DiagramScene(QMenu *itemMenu, MainWindow *ownerWindow,
                           QObject *parent)
    : QGraphicsScene(parent)
{
    myOwnerWindow = ownerWindow;
    myItemMenu = itemMenu;
    myMode = MoveItem;

    line = 0;
    textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
    snapToGrid=1;
    myGrid=10;
    myPolygonPath=0;
    myCorners=0;

    TitleText = new DiagramTextItem(0,0,1,0xFFF,255,"BLOCK NAME HERE not visible",
                                    QPointF(500,420));
    TitleText->setZValue(1000);
    addItem(TitleText);

}

void DiagramScene::drawBackground(QPainter *p, const QRectF &r)
{
	p -> save();	
	
	p -> setRenderHint(QPainter::Antialiasing, false);
	p -> setRenderHint(QPainter::TextAntialiasing, true);
	p -> setRenderHint(QPainter::SmoothPixmapTransform, false);
		
	p -> setPen(Qt::NoPen);
	p -> setBrush(Qt::white);
	p -> drawRect(r);
	

        p -> setPen(Qt::gray);
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

    p->drawLine(500,0,500,1000);
    p->drawLine(0,500,1000,500);

	p -> restore();
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

QString DiagramScene::createPrototype()
{
    bool first = 1;
    QString functionPrototype = "\nvoid " +
                                TitleText->toPlainText().replace(' ','_') + "(";

    foreach (QGraphicsItem *item, this->items()) {
        if (item->type() == DiagramTextItem::Type) {            
            int styleIO = qgraphicsitem_cast<DiagramTextItem*>(item)->styleIO();
            if(styleIO<256)
            {
              int ioID = qgraphicsitem_cast<DiagramTextItem*>(item)->textID();
              if(!first) functionPrototype += ","; first = 0;
              switch(styleIO&127)
              {              
                  case 1:
                      functionPrototype += "bool ";
                      break;
                  case 2:
                      functionPrototype += "char ";
                      break;
                  case 3:
                      functionPrototype += "int ";
                      break;
                  case 4:
                      functionPrototype += "double ";
                      break;
                  case 5:
                      functionPrototype += "float ";
                      break;
                  case 6:
                      functionPrototype += "short int ";
                      break;
                  case 7:
                      functionPrototype += "long int ";
                      break;
                  case 8:
                      functionPrototype += "unsigned char ";
                      break;
                  case 9:
                      functionPrototype += "unsigned integer ";
                      break;
                  case 10:
                      functionPrototype += "unsigned short int ";
                      break;
                  case 11:
                      functionPrototype += "unsigned long int ";
                      break;
                  default:;
              }
              functionPrototype += (styleIO>>7)? "in":"&out";
              functionPrototype += "_" + QString::number(ioID);
            }
        }
    }

    functionPrototype += ") {";
    return functionPrototype;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);
    myOwnerWindow->updateProt();

    QString Text;
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    int addResult=0;

    switch (myMode)
    {
        case InsertText:            
            //TODO: limit text items to 255 maximum
            if(myTextType<256)
                if(myTextType & 0b10000000)
                    Text = "IN " +myTypeString;
                else
                    Text = "OUT " +myTypeString;
            else
                Text = myTypeString;

            textItem = new DiagramTextItem(0,0,1,myTextType,0,Text,
                                           mouseEvent->scenePos());
            addResult=addTextItem(textItem);
            if(addResult!=-1)
            {
                textItem->setZValue(1000.0);
                addItem(textItem);
                textItem->setTextID(addResult);
            }
            else
            {
                delete(textItem);
                QMessageBox::warning(0,"Full","The block can only have "
                                     "255 labels/IOs.");
            }
            emit textInserted(textItem);
            break;
        case EditPolygon:
            if(line == 0 && items().indexOf(myPolygonPath)==-1)
            {
                line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
                line->setPen(QPen(Qt::blue, 2));
                line->setZValue(1000.0);
                addItem(line);
            }
            else if(line != 0 && items().indexOf(myPolygonPath)==-1 &&
                    line->line().length()>5)
            {
                myPolygonPath = new Arrow(line->line().p1(),line->line().p2(),
                                          0,this);                
                QLineF newLine(line->line().p2(),line->line().p2());
                line->setLine(newLine);               
            }            
            else if(line != 0 && items().indexOf(myPolygonPath)!=-1 &&
                    line->line().length()>5)
            {                
                myPolygonPath->createCorner(line->line().p1(),myCorners);               
                myPolygonPath->setEndPoint(line->line().p2());
                myPolygonPath->updatePosition();
                QLineF newLine(line->line().p2(),line->line().p2());
                line->setLine(newLine);

                myCorners++;
            }

        case MoveItem:
            QGraphicsScene::mousePressEvent(mouseEvent);
            break;
        default: ;
    }

}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);
    if (myMode == EditPolygon && line != 0 )
    {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    QPointF mousePos = mouseEvent->scenePos();
    mousePos.setX(mousePos.x()-500);
    mousePos.setY(-(mousePos.y()-500));

    QString barMesg= QString("X[%1] Y[%2]").arg(QString::number(mousePos.x()))
                                           .arg(QString::number(mousePos.y()));

    foreach (QGraphicsItem *item, this->items(mouseEvent->scenePos())) {
        if (item->type() == DiagramTextItem::Type) {
            if(qgraphicsitem_cast<DiagramTextItem *>(item)->styleIO()<256)
            {
                barMesg  +=
                    tr(" ** Over In/Out text label with {ID = ") +
                    QString::number(qgraphicsitem_cast<DiagramTextItem *>
                              (item)->textID()) + tr("}");
            }
            else if(qgraphicsitem_cast<DiagramTextItem *>(item)->styleIO()==256)
            {
                barMesg  +=
                    tr(" ** Over text label with {ID = ") +
                    QString::number(qgraphicsitem_cast<DiagramTextItem *>
                              (item)->textID()) + tr("}");
            }
            else if(qgraphicsitem_cast<DiagramTextItem *>(item)->styleIO()==257)
            {
                barMesg  +=                    
                    tr(" ** Over editable text label with {ID = ") +
                    QString::number(qgraphicsitem_cast<DiagramTextItem *>
                              (item)->textID()) + tr("}");
            }
        }
    }
    myOwnerWindow->statusBar->showMessage(barMesg);

}

void DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);
    if  (myMode == EditPolygon && line != 0 && myCorners>0)
    {        
        if(myPolygonPath->getStartPoint()!=line->line().p2())
            myPolygonPath->createCorner(line->line().p2(),myCorners);

        myPolygonPath->setEndPoint(myPolygonPath->getStartPoint());
        myPolygonPath->createFirstCorner();
        myPolygonPath->updatePosition();
        myCorners=0;
        removeItem(line);
        line = 0;
        myMode = MoveItem;
        emit textInserted(textItem);//Is the same for all buttons
    }
    else if  (myMode != EditPolygon)
    {
       QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
    }    
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    doSnapToGrid(mouseEvent);
   if(myMode != EditPolygon && line == 0)
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

QDomDocument DiagramScene::toXmlFormat()
{
    QDomDocument document;
    QDomComment initialComments=document.createComment(
        "File for SIE Code Generator. Custmos Blocks");
    document.appendChild(initialComments);

    QDomElement diagram = document.createElement("CustomItem");
    diagram.setAttribute("BlockName",TitleText->toPlainText());
    document.appendChild(diagram);

    //Lists of items
    QList<DiagramTextItem *> Items;
    QList<Arrow *> Arrows;
    foreach(QGraphicsItem *item, items())
    {
        if(item->type() == DiagramTextItem::Type)
            Items.append(qgraphicsitem_cast<DiagramTextItem *>(item));
        else if(item->type() == Arrow::Type)
            Arrows.append(qgraphicsitem_cast<Arrow *>(item));
    }

    if(Arrows.count()>1) {printf("Something is wrong.\n"); fflush(stdout);}

    //Create the XML structure
    if(myPolygonPath!=0)
        diagram.appendChild(myPolygonPath->toXml(document));

    QDomElement element;
    if(Items.count()>0)
    {
        QDomElement textItems = document.createElement("TextItems");
        foreach(DiagramTextItem *item, Items)
        {
            if(item->styleIO() != 0xFFF)
            {
                element = item->toXml(document);                
                element.setAttribute("ID",textItemsByID.key(item));
                textItems.appendChild(element);                
            }
        }
        diagram.appendChild(textItems);
    }


    //Add the code as CDATA sections
    //Order: Header Code, Init Code, Block Code and Extra Code.

    QDomCDATASection headerCode=document.createCDATASection(
            myOwnerWindow->headerTextEdit->toPlainText());
    diagram.appendChild(headerCode);

    QDomCDATASection initCode=document.createCDATASection(
            myOwnerWindow->initTextEdit->toPlainText());
    diagram.appendChild(initCode);

    QDomCDATASection blockCode=document.createCDATASection(
            myOwnerWindow->blockTextEdit->toPlainText());
    diagram.appendChild(blockCode);

    QDomCDATASection extraCode=document.createCDATASection(
            myOwnerWindow->extraTextEdit->toPlainText());
    diagram.appendChild(extraCode);

    return(document);
}

int DiagramScene::fromXmlFormat(QDomDocument document)
{
    //Read items TODO: in future... add multi items on same file    
    QDomNodeList customsItems = document.elementsByTagName("CustomItem");
    if(!customsItems.at(0).isElement())
        return -1;
    //Load the first item in the document
    QDomElement customItem = customsItems.at(0).toElement();
    if(customItem.attribute("BlockName")=="")
        TitleText->setPlainText("Please set Block Name");
    else
        TitleText->setPlainText(customItem.attribute("BlockName"));

    TitleText->updatePosition();
    int codeIdx = 0;

    for (QDomNode node = customItem.firstChild() ;
         !node.isNull() ;
         node = node.nextSibling())
    {       
      if(node.isCDATASection())
      {
          QDomCDATASection Code = node.toCDATASection();
          switch(codeIdx)
          {
            case 0:
                myOwnerWindow->headerTextEdit->setPlainText(Code.data());
                break;
            case 1:
                myOwnerWindow->initTextEdit->setPlainText(Code.data());
                break;
            case 2:
                myOwnerWindow->blockTextEdit->setPlainText(Code.data());
                break;
            case 3:
                myOwnerWindow->extraTextEdit->setPlainText(Code.data());
                break;
            default:
                QMessageBox::warning(0,"Parsing XML", tr("Extra CDATA found in")
                                   +tr(" file, this section will be ignored."));
          }
          codeIdx++;
      }
      else
      {
        QDomElement element = node.toElement();
        if(element.tagName()=="Polygon")
        {
            QList<QPointF> points;
            for (QDomNode node = element.firstChild() ;
                             !node.isNull() ;
                             node = node.nextSibling())
            {
                QDomElement point = node.toElement();
                if(point.tagName()!="Point")
                    return -1;
                points.append(QPointF((QPointF(point.attribute("x").toFloat(),0)
                                              +QPointF(500,500)).x(),
                                     (QPointF(0,point.attribute("y").toFloat())
                                              +QPointF(500,500)).y()));
            }

            if(points.count()>0)
            {                
                myPolygonPath = new Arrow(points.at(0),points.at(0),0,this);
                for(int i=1; i< points.count();i++)
                {
                     myPolygonPath->createCorner(points.at(i),i-1);
                }
                myPolygonPath->createFirstCorner();
                myPolygonPath->updatePosition();
            }
        }
        else if(element.tagName()=="TextItems")
        {            
            for (QDomNode node = element.firstChild() ;
                             !node.isNull() ;
                             node = node.nextSibling())
            {
                QDomElement textItemE = node.toElement();
                if(textItemE.tagName()!="TextItem")
                    return -1;

                int myStyleIO = textItemE.attribute("myStyleIO").toInt();
                int myID = textItemE.attribute("ID").toInt();

                bool editableItem = textItemE.attribute("editableItem").toInt();
                QPointF posOffset=
                        QPointF((QPointF(textItemE.attribute("posOffset-x")
                                         .toFloat(),0)+QPointF(500,500)).x(),
                               (-QPointF(0,textItemE.attribute("posOffset-y")
                                         .toFloat())+QPointF(500,500)).y());
                QString itemString=textItemE.attribute("text");

                if(myStyleIO==0)
                {
                    if(!editableItem)
                        myStyleIO=256;
                    else
                        myStyleIO=257;
                }

                DiagramTextItem * newTextItem =
                 new DiagramTextItem(0,0,1,myStyleIO,myID,itemString,posOffset);
                newTextItem->setZValue(1000.0);
                addItem(newTextItem);

                if(textItemsByID.find(myID)!=textItemsByID.end())
                {
                    int result=addTextItem(newTextItem);
                    QMessageBox::warning(0,"ID Problems",
                        tr("Label with ID[")+QString::number(myID)+
                        tr("] already exists, this will be reasigned to [")+
                        QString::number(result)+
                        tr("] for prevent problems."));
                    newTextItem->setTextID(result);
                }
                else
                    textItemsByID.insert(myID,newTextItem);
            }
        }
      }
    }
    myOwnerWindow->updateProt();
    return 1;
}

void DiagramScene::cleanScene()
{
    //Lists of items
    QList<DiagramTextItem *> Items;
    foreach(QGraphicsItem *item, items())
    {
        if(item->type() == DiagramTextItem::Type)
            Items.append(qgraphicsitem_cast<DiagramTextItem *>(item));
    }
    //Remove Diagram Text Items
    foreach(DiagramTextItem *item, Items)
    {
        if(item->styleIO() != 0xFFF)
        {
            removeItem(item);
            delete(item);
        }
    }
    //Remove Polygon Path
    if(items().indexOf(myPolygonPath)!=-1)
    {
        myPolygonPath->removeLines();
        removeItem(myPolygonPath);
        delete(myPolygonPath);
    }
    TitleText->setPlainText("BLOCK NAME HERE not visible");
    TitleText->updatePosition();
    this->addItem(TitleText);
    textItemsByID.clear();
}

int DiagramScene::addTextItem(DiagramTextItem * textItem)
{
    for(int i=0; i<256; i++)
    {
        QHash<int,DiagramTextItem *>::iterator iter= textItemsByID.find(i);
        if(iter==textItemsByID.end())
        {
            textItemsByID.insert(i,textItem);
            return i;
        }
    }
    return -1;
}

void DiagramScene::removeTextItem(DiagramTextItem * textItem)
{
    textItemsByID.remove(textItemsByID.key(textItem));
}

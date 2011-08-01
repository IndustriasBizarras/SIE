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
#include <QLabel>

#include "mainwindow.h"

const int InsertTextButton = 100000;

MainWindow::MainWindow()
{
    domElementsByName=0;
    buttonGroup=0;
    toolBox=0;
    statusBar = new QStatusBar(this);
    createActions();
    createMenus();
    scene = new DiagramScene(itemMenu,this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(DiagramItem*)),
            this, SLOT(itemInserted(DiagramItem*)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
        this, SLOT(textInserted(QGraphicsTextItem*)));
    createToolBox();
    createToolbars();
    setDefaultOptions();

    setWindowTitle(tr("SIE Code Generator (Diagram Editor)"));
    setUnifiedTitleAndToolBarOnMac(true);    
    myFilePath = "";
    libDialog=0;
    cgDialog=0;
    optionsDialog=0;
    sieSSH=0;
    compile=0;
    sshReady=0;
    dontDelete=0;
    if(QApplication::argc()>1)
        {newDiagram(QString(QApplication::argv()[1]));}
    else
        newDiagram();
    statusBar->showMessage("Ready...");
    this->setStatusBar(statusBar);
}

void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
    if (myButton != button)
        button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

    scene->update();
    view->update();
}

void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
    if (buttonGroup->button(id) != button)
        button->setChecked(false);
    }
    if (id == InsertTextButton) {
        scene->setMode(DiagramScene::InsertText);
    } else {
        scene->setItemType(buttonGroup->button(id)->text()); //Block name
        scene->setMode(DiagramScene::InsertItem);
    }
}

void MainWindow::deleteItem()
{
  if(!dontDelete)
  {
    if(!scene->selectedItems().isEmpty())
        scene->saveUndoState();
    //List od items
    QList<DiagramItem *> Items;
    QList<Arrow *> Arrows;
    QList<lineItem *> Lines;
    QList<DiagramTextItem *> TextItems;    
    foreach(QGraphicsItem *item, scene->selectedItems())
    {
        if(item->type() == DiagramItem::Type)
            Items.append(qgraphicsitem_cast<DiagramItem *>(item));
        else if(item->type() == Arrow::Type)
            Arrows.append(qgraphicsitem_cast<Arrow *>(item));
        else if(item->type() == lineItem::Type)
            Lines.append(qgraphicsitem_cast<lineItem *>(item));
        else if(item->type() == DiagramTextItem::Type)
            if(qgraphicsitem_cast<DiagramTextItem *>(item)->ownerItem() == 0)
                TextItems.append(qgraphicsitem_cast<DiagramTextItem *>(item));
    }

    foreach(DiagramItem * item, Items){
        item->removeArrows();
        item->removeTextItems();
        scene->removeDiagramItem(item);
        scene->removeItem(item);
        delete(item);
    }

    foreach(Arrow * item, Arrows){
        if(scene->items().contains(item))
        {
            item->removeLines();
            item->startItem()->ownerItem()->removeArrow(item);
            item->endItem()->ownerItem()->removeArrow(item);
            scene->removeItem(item);        
            delete(item);
        }
    }

    foreach(lineItem * item, Lines){
        if(!item->itemIsMovable() && scene->items().contains(item))
        {
            item->myOwner()->removeLine(item);
            item->myOwner()->updatePosition();
            scene->removeItem(item);
            delete(item);
        }
    }

    foreach(DiagramTextItem * item, TextItems){
        scene->removeItem(item);
        delete(item);
    }

  }
}

void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::cgGroupClicked()
{    
    QList<DiagramItem *> allItems;
    QList<DiagramItem *> headItems;
    QList<DiagramItem *> passItems;
    QList<Arrow *> passArrows;
    QString headerCode;
    QString initCode;
    QString blockCode;
    QString extraCode;
    QString mainCode;
    QString iosCode;
    QString warnings;
    QString mainSCode;

    // Find all Diagram Items and select the "heads" (has no inputs)
    foreach (QGraphicsItem *item, scene->items()) {
        if (item->type() == DiagramItem::Type)
        {
            allItems.append(qgraphicsitem_cast<DiagramItem *>(item));
            if(itemIsHead(qgraphicsitem_cast<DiagramItem *>(item)))
                headItems.append(qgraphicsitem_cast<DiagramItem *>(item));
        }
    }
    // Get code for segments with heads-ends
    foreach(DiagramItem * item, headItems)
    {
        passItem(item,passItems,passArrows, headerCode, initCode, blockCode,
                 extraCode, mainCode, iosCode, warnings, mainSCode);
    }
    // Get code for items in segments with no heads-ends
    foreach(DiagramItem * item, allItems)
    {
        if(!passItems.contains(item))
            passItem(item,passItems,passArrows,headerCode,initCode,
                 blockCode,extraCode,mainCode,iosCode,warnings,mainSCode);
    }

    if(mainSCode.contains("/***![SYSTEM WHILE]***/"))
        mainSCode = mainSCode.replace("/***![SYSTEM WHILE]***/",mainCode);
    else if(mainSCode.contains("/***![SYSTEM TIMER]***/"))
        mainSCode = mainSCode.replace("/***![SYSTEM TIMER]***/",mainCode);
    else
        mainSCode = mainCode;

    // create work dir
    QString tempWorkDir = workDir+"/"+executableFile;
    if(!QDir(tempWorkDir).exists())
    {
        warnings += tr("\nExecuting command:  mkdir ") +
                      tempWorkDir + tr("/") + tr("\n");
        warnings += callexternapp("mkdir ",workDir + tr("\n"));
        warnings += callexternapp("mkdir ",tempWorkDir + tr("\n"));
    }
    // Copy files from template
    if(QDir(templateDir).exists())
    {
        warnings += tr("\nExecuting command:  cp -fR ") +
                    templateDir+tr("/. ")+
                    tempWorkDir+tr("/");
        warnings += callexternapp(tr("cp -fR ") +
                    templateDir+tr("/. ")+
                    tempWorkDir+tr("/"),"");
    }
    else
    {
        warnings += tr("\nWARNING*** Could not found template files");
    }

    //TODO: Makefile creation!!!


    //Open main code template
    QString protoCode,tempTemplateFile;
    tempTemplateFile = tempWorkDir+tr("/")+templateFile;
    if(!QFileInfo(tempTemplateFile).isReadable())
    {
        warnings +="\nERROR***: "
                   "Main code template file is not readable or not exists.";
        protoCode+="Main code template file is not readable or not exists.";
    }
    else
    {
        warnings +=tr("\nOpening File: ") + tempTemplateFile;
        QFile file(tempTemplateFile);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray text = file.readAll();
            protoCode = text.data();
            file.close();
        }
        else
            warnings += "\nERROR***: "
                        "Could not open main code template file for read.";

        warnings +=tr("\nReplacing code on main code template");
        protoCode.replace("/***![HEADER SECTION]***/",headerCode);
        protoCode.replace("/***![BLOCK SECTION]***/",blockCode);
        protoCode.replace("/***![INIT SECTION]***/",initCode);
        protoCode.replace("/***![IO SECTION]***/",iosCode);
        protoCode.replace("/***![MAIN SECTION]***/",mainSCode);
        protoCode.replace("/***![EXTRA SECTION]***/",extraCode);
    }


    //Open Makefile template
    QString protoMake,tempMakeFile;
    tempMakeFile = tempWorkDir+tr("/")+makeFile;
    if(!QFileInfo(makeFile).isReadable())
    {
        warnings +="\nERROR***: "
                   "Makefile template file is not readable or not exists.";
        protoMake+="Makefile template file is not readable or not exists.";
    }
    else
    {
        warnings +=tr("\nOpening File: ") + tempMakeFile;
        QFile file(tempMakeFile);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray text = file.readAll();
            protoMake = text.data();
            file.close();
        }
        else
            warnings +="\nERROR***: "
                       "Could not open Makefile template file for read.";
        warnings +=tr("\nReplacing code on Makefile template");
        protoMake.replace("![MIPS TOOLCHAIN]",mipsToolChainDir);
        protoMake.replace("![MIPS TOOLCHAIN BASE]",mipsToolChain);
        protoMake.replace("![SIE APP NAME]",executableFile);
        protoMake.replace("![MAIN TEMPLATE]",templateFile);
        protoMake.replace("![MAIN OBJECT]",
                          QFileInfo(templateFile).baseName()+".o");

    }

    //Open code generator form
    codeForm();

    // Update form:
    cgUi->codeTextEdit->setPlainText(protoCode);
    cgUi->makeTextEdit->setPlainText(protoMake);
    saveTemplates();
    cgUi->logTextEdit->append(warnings);
    cgUi->codesTab->setCurrentIndex(0);
    cgUi->outputsTab->setCurrentIndex(0);
}

void MainWindow::saveTemplates()
{
    QString tempWorkDir = workDir+"/"+executableFile;
    //Save files from templates
    QFile file(tempWorkDir+"/"+templateFile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << cgUi->codeTextEdit->toPlainText();
        file.close();
    }
    else
        cgUi->logTextEdit->append(
                "ERROR*** Could not open main code file for write.");

    file.setFileName(tempWorkDir+tr("/")+makeFile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << cgUi->makeTextEdit->toPlainText();
        file.close();
    }
    else
        cgUi->logTextEdit->append(
                "ERROR*** Could not open Makefile for write.");
}

QString MainWindow::passItem(DiagramItem * item,
                             QList<DiagramItem *> &passItems,
                             QList<Arrow *> &passArrows,
                             QString &headerCode,
                             QString &initCode,
                             QString &blockCode,
                             QString &extraCode,
                             QString &mainCode,
                             QString &iosCode,
                             QString &warnings,
                             QString &mainSCode)
{  
if(!passItems.contains(item))
{
    QHash<int , DiagramItem *> DiagramsID = scene->getDiagramsID();
    // Get Dom Element: From item
    QDomElement * itemDomElement = item->getDomElement();
    // Get basic information
    QString blockID = QString::number(DiagramsID.key(item));

    QString blockName = itemDomElement->attribute("BlockName");

    QList<DiagramTextItem *> TextItems =item->getTextItems();

    // Create list de ios and values, and get function prototye
    QList <QString> ioTypes;
    QList <QString> ioNames;
    QList <QString> valueNames;
    QList <QString> values;
    QList <DiagramTextItem *> inputs;
    QList <DiagramTextItem *> outputs;

    QString protoFunction = createPrototype(
       TextItems,ioTypes,ioNames,valueNames,values,
       blockName+blockID,inputs,outputs);

    // Read Code:
    int codeIdx = 0;
    QString headerCodet;
    QString initCodet;
    QString blockCodet;
    QString extraCodet;
    for (QDomNode node = itemDomElement->firstChild() ;
        !node.isNull() ;
        node = node.nextSibling())
    {
     if(node.isCDATASection())
     {
         QDomCDATASection Code = node.toCDATASection();
         switch(codeIdx)
         {
           case 0:
               headerCodet=(Code.data());
               break;
           case 1:
               initCodet=(Code.data());
               break;
           case 2:
               blockCodet=(Code.data());
               break;
           case 3:
               extraCodet=(Code.data());
               break;
           default:;
         }
         codeIdx++;
     }
    }
    // Replace values:
    for(int i = 0; i<values.count(); i++)
    {
       headerCodet=headerCodet.replace(valueNames[i],values[i]);
       initCodet=initCodet.replace(valueNames[i],values[i]);
       blockCodet=blockCodet.replace(valueNames[i],values[i]);
       extraCodet=extraCodet.replace(valueNames[i],values[i]);
    }

    if(blockName == "System While" ||
       blockName == "System Timer")
    {
        foreach(QString ioName, ioNames)
            blockCodet.replace(ioName,ioName+"_"+blockID);

        mainSCode += blockCodet;
    }
    else
    {
        headerCode+= headerCodet;
        initCode+= initCodet ;
        blockCode+= tr("\n")+protoFunction+tr("\n{\n")+blockCodet + tr("\n}\n");
        extraCode+= extraCodet;
    }            

    iosCode += tr("\t//Inputs/Outputs: Block: <") + blockName +
               tr("> with ID[") + blockID + tr("] \n");
    // Generate inputs/outputs and function declaration
    QString prototype = tr("\t") + QString(blockName + blockID)
                        .replace(' ','_') + tr(" (");
    int first = 0;
    for(int i = 0; i<ioNames.count(); i++)
    {
        iosCode += tr("\t") + ioTypes.at(i) +
                  ioNames.at(i) + tr("_")+blockID + tr("=0;\n");
        prototype += first? tr(", "):tr(" ");
        prototype += ioNames.at(i) + tr("_") + blockID;
        first =1;
    }
    prototype += tr(");\n");   

    // Connect the inputs to outputs
    QList<DiagramTextItem *> connectedInputs;
    QList<DiagramTextItem *> connectedOutputs;
    foreach(Arrow *arrow, item->getArrows()){
        if(item == arrow->endOwner())
        {
            mainCode += tr("\tin_") +
                        QString::number(arrow->endItem()->textID()) +
                        tr("_") +
                        QString::number(arrow->endOwner()->getID()) +
                        tr(" = out_") +
                        QString::number(arrow->startItem()->textID()) +
                        tr("_") +
                        QString::number(arrow->startOwner()->getID()) +
                        tr(";\n");
            connectedInputs.append(arrow->endItem());
        }
    }
    // Find unconnected inputs
    foreach(DiagramTextItem * item, inputs){
        if(!connectedInputs.contains(item))
            warnings += tr("\nWARNING** Unconnected input[") +
                        QString::number(item->textID()) +
                        tr("] in block ") + blockName +
                        tr(" with ID [") + blockID + tr("]\n");
    }

    if(blockName != "System While" &&
       blockName != "System Timer")
    {
        mainCode +=   prototype;
    }

    passItems.append(item);

    // Apply passItem to items connected to the outputs
    foreach(Arrow *arrow, item->getArrows()){
        if(item == arrow->startOwner())
        {
            passItem(arrow->endOwner(),passItems,passArrows,
                     headerCode, initCode, blockCode,
                     extraCode, mainCode, iosCode,
                      warnings, mainSCode);
            connectedOutputs.append(arrow->startItem());
        }
    }
    // Find unconnected outputs
    foreach(DiagramTextItem * item, outputs){
        if(!connectedOutputs.contains(item))
            warnings += tr("\nWARNING** Unconnected output[") +
                        QString::number(item->textID()) +
                        tr("] in block ") + blockName +
                        tr(" with ID [") + blockID + tr("]\n");
    }
}

    return 0;
}

bool MainWindow::itemIsHead(DiagramItem * item)
{
    foreach (DiagramTextItem *text, item->getTextItems())
    {
        if(text->styleIO()>>7)
            return 0;
    }
    return 1;
}

bool MainWindow::itemIsEnd(DiagramItem * item)
{
    foreach (DiagramTextItem *text, item->getTextItems())
    {
        if(!text->styleIO()>>7)
            return 0;
    }
    return 1;
}

QString MainWindow::getIoType(DiagramTextItem * item)
{
    QString ioType;
    switch(item->styleIO()&127)
    {
        case 1:
            ioType += "bool ";
            break;
        case 2:
            ioType += "char ";
            break;
        case 3:
            ioType += "int ";
            break;
        case 4:
            ioType += "double ";
            break;
        case 5:
            ioType += "float ";
            break;
        case 6:
            ioType += "short int ";
            break;
        case 7:
            ioType += "long int ";
            break;
        case 8:
            ioType += "unsigned char ";
            break;
        case 9:
            ioType += "unsigned int ";
            break;
        case 10:
            ioType += "unsigned short int ";
            break;
        case 11:
            ioType += "unsigned long int ";
            break;
        default:
            ioType += "<unknow type> ";;
    }
    return ioType;
}

QString MainWindow::createPrototype(QList <DiagramTextItem *> &textItems,
                                    QList <QString> &ioTypes,
                                    QList <QString> &ioNames,
                                    QList <QString> &valueNames,
                                    QList <QString> &values,
                                    QString blockNameID,
                                    QList <DiagramTextItem *> &inputs,
                                    QList <DiagramTextItem *> &outputs)
{
    foreach (DiagramTextItem *item, textItems) {
        int styleIO = item->styleIO();
        if(styleIO<256 && styleIO>0)
        {
          QString ioType, ioName;
          int ioID = item->textID();
          ioType = getIoType(item);
          ioName = ((styleIO>>7)? tr("in"):tr("out")) + "_" +
                    QString::number(ioID);
          if(styleIO>>7)
          {
                ioName  =   tr("in") + "_" + QString::number(ioID);
                inputs.append(item);
          }
          else
          {
                ioName  =   tr("out") + "_" + QString::number(ioID);
                outputs.append(item);
          }
          ioTypes.append(ioType);
          ioNames.append(ioName);
        }
        else if(item->isEditable())
        {
          QString valueName = tr("value_") + QString::number(item->textID());
          values.append(item->toPlainText());
          valueNames.append(valueName);
        }
    }


    QString prototype = tr("void ") + blockNameID.replace(' ','_') + tr(" (");
    if(!ioNames.isEmpty())
    {
        int first = 0;
        for(int i = 0; i<ioNames.count(); i++)
        {
            prototype += first? tr(", "):tr(" ");

            prototype += ioTypes.at(i);
            if(ioNames.at(i).contains("out"))            
                 prototype += tr("&") + ioNames.at(i);
            else
                 prototype += ioNames.at(i);

            first =1;
        }
    }
    prototype += ")";
    return prototype;
}

void MainWindow::bringToFront()
{
    sendTo(1);
}

void MainWindow::sendToBack()
{
    sendTo(0);
}

void MainWindow::sendTo(bool value)
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue &&
            item->type() == DiagramItem::Type)
        {
            if(value)
                zValue = item->zValue() + 0.1;
            else
                zValue = item->zValue() - 0.1;
        }
    }
    selectedItem->setZValue(zValue);
    if(selectedItem->type() == DiagramItem::Type)
        foreach (DiagramTextItem *texts,
                qgraphicsitem_cast<DiagramItem *>(selectedItem)->getTextItems())
        {
            texts->updatePosition();
        }

}

void MainWindow::itemInserted(DiagramItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(buttonIdByName.value(item->diagramType()))->setChecked(false);
}

void MainWindow::textInserted(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}

void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                ":/images/textpointer.png",
                qVariantValue<QColor>(textAction->data())));
    textButtonTriggered();
}

void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/images/floodfill.png",
                 qVariantValue<QColor>(fillAction->data())));
    fillButtonTriggered();
}

void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/images/linecolor.png",
                 qVariantValue<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void MainWindow::textButtonTriggered()
{
    scene->setTextColor(qVariantValue<QColor>(textAction->data()));
}

void MainWindow::fillButtonTriggered()
{
    scene->setItemColor(qVariantValue<QColor>(fillAction->data()));
}

void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qVariantValue<QColor>(lineAction->data()));
}

void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setBold(boldAction->isChecked());
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}

void MainWindow::setFontSettings(QFont font)
{
    fontSizeCombo->setEditText(QString::number(font.pointSize()));
    font.bold()? boldAction->setChecked(true): boldAction->setChecked(false);
    font.italic()?  italicAction->setChecked(true):
                    italicAction->setChecked(false);
    font.underline()?   underlineAction->setChecked(true):
                        underlineAction->setChecked(false);
    fontCombo->setEditText(font.family());
}

void MainWindow::about()
{
    QMessageBox::question(this, tr("About SIE Code Generator"),
                       tr("TODO <b>:)</b>"));
}

void MainWindow::cleanDomElementsByName()
{
    if(domElementsByName!=0)
    {
        foreach(QDomElement * domElement,domElementsByName->values())
            {delete(domElement);}
        delete(domElementsByName);
    }
}

void MainWindow::addLibrariesButtons(QGridLayout *layout)
{
    int i = 1;
    cleanDomElementsByName();
    domElementsByName = new QHash<QString , QDomElement*>;
    buttonIdByName.clear();
    QDomDocument customItems;
    foreach(QString filepath, libraryList)
    {        
        customItems = parseDocument(filepath);        
        for (QDomNode node = customItems.firstChild() ;
             !node.isNull() ;
             node = node.nextSibling())
        {
            QDomElement *customItem = new QDomElement(node.toElement());
            if(customItem->tagName()=="CustomItem")
            {
                if(domElementsByName->contains(
                        customItem->attribute("BlockName")))
                {
                    QMessageBox::warning(this,"Block name in use.",
                                         "The library " + filepath +
                                         " has one block called" +
                                         customItem->attribute("BlockName") +
                                         " that is already in use. Only the "
                                         " first Block loaded can be used, this"
                                         " library will be ignored.");
                }
                else
                {
                    domElementsByName->insert(customItem->attribute("BlockName"),
                                             customItem);
                    buttonIdByName.insert(customItem->attribute("BlockName"),i-1);                    
                    scene->setDomElementsByName(domElementsByName);
                    scene->setButtonIdByName(buttonIdByName);

                    layout->addWidget(createCellWidget(
                            customItem->attribute("BlockName"),
                            domElementsByName->
                            value(customItem->attribute("BlockName"))),i/2,i&1);
                    i++;
                }                
            }            
        }
    }
}



void MainWindow::createToolBox()
{
    if(buttonGroup!=0) delete(buttonGroup);
    if(toolBox!=0) delete(toolBox);
    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));

    QGridLayout *layout = new QGridLayout;

    addLibrariesButtons(layout);

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")
                        .scaled(30, 30)));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 0, 0);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic blocks"));
    //toolBox->addItem(backgroundWidget, tr("Backgrounds"));

    //Add tool box to window
    QGridLayout *newLayout = new QGridLayout;
    newLayout->addWidget(toolBox,0,0);
    view = new QGraphicsView(scene);
    newLayout->addWidget(view,0,1);

    QWidget *widget = new QWidget;
    widget->setLayout(newLayout);

    setCentralWidget(widget);
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()),
            this, SLOT(bringToFront()));

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"),
                                 tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+B"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()),
        this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"),
                               tr("&Delete"), this);
    deleteAction->setShortcut(tr("Ctrl+Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()),
        this, SLOT(deleteItem()));


    newAction = new QAction(QIcon(":/images/new.png"),tr("&New"),this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip("New diagram");
    connect(newAction,SIGNAL(triggered()),this,SLOT(newDiagram()));

    saveAction = new QAction(QIcon(":/images/save.png"),tr("&Save"),this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip("Save current diagram");
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveDiagram()));

    saveAsAction = new QAction(QIcon(":/images/save_as.png"),
                               tr("Save &As..."),this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("Save current diagram with another name");
    connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAsDiagram()));

    openAction = new QAction(QIcon(":/images/open.png"),tr("&Open"),this);    
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip("Open diagram");
    connect(openAction,SIGNAL(triggered()),this,SLOT(openDiagram()));

    exportImgAction = new QAction(tr("&Export to ..."),this);
    exportImgAction->setStatusTip("Export current diagram to picture");
    connect(exportImgAction,SIGNAL(triggered()),this,SLOT(exportDiagram()));


    redoAction = new QAction(QIcon(":/images/redo.png"),tr("&Redo"),this);
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->setStatusTip("Redo changes on diagram");
    connect(redoAction,SIGNAL(triggered()),this,SLOT(redoDiagram()));

    undoAction = new QAction(QIcon(":/images/undo.png"),tr("&Undo"),this);
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setStatusTip("Undo changes on diagram");
    connect(undoAction,SIGNAL(triggered()),this,SLOT(undoDiagram()));


    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit diagram editor"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    boldAction = new QAction(QIcon(":/images/bold.png"),tr("Bold"), this);
    boldAction->setCheckable(true);
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()),
            this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"),
                               tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered(bool)),
            this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"),
                                  tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered(bool)),
            this, SLOT(handleFontChange()));



    libraryAction = new QAction(tr("&Library..."),this);
    libraryAction->setStatusTip(tr("Add, Remove or edit libraries"));
    connect(libraryAction, SIGNAL(triggered()),
            this, SLOT(libraryForm()));

    optionsAction = new QAction(tr("&Options"),this);
    optionsAction->setShortcuts(QKeySequence::Preferences);
    optionsAction->setStatusTip(tr("Edit options"));
    connect(optionsAction, SIGNAL(triggered()),
            this, SLOT(optionsForm()));

    aboutAction = new QAction(tr("A&bout"), this);
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exportImgAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    preferencesMenu= menuBar()->addMenu(tr("&Preferences"));
    preferencesMenu->addAction(libraryAction);
    preferencesMenu->addAction(optionsAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    QToolButton *cgButton = new QToolButton;
    cgButton->setCheckable(false);
    cgButton->setIcon(QIcon(":/images/cg.png"));
    cgButton->setToolTip("Generate code for SIE");

    cgGroup = new QButtonGroup;
    cgGroup->addButton(cgButton,0);

    connect(cgGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(cgGroupClicked()));

    cgToolbar = addToolBar(tr("Code Generator"));
    cgToolbar->addWidget(cgButton);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);

    fontCombo = new QFontComboBox();
    fontSizeCombo = new QComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()),
                                                 Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(
    ":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()),
                         Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
    ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()),
                                 Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup;
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton,
                                int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));


    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

    gridButton = new QToolButton;
    gridButton->setCheckable(true);
    gridButton->setChecked(false);
    gridButton->setIcon(QIcon(":/images/grid.png"));

    connect(gridButton,SIGNAL(clicked()),this,SLOT(setGridState()));

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);
    colorToolBar->addWidget(gridButton);

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

}

void MainWindow::setGridState()
{
    scene->setDawGrid(gridButton->isChecked());
    scene->update();
}

QWidget *MainWindow::createCellWidget(QString text, QDomElement *customItem)
{
    DiagramItem item(itemMenu,text,customItem);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, buttonIdByName.value(text));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors  << Qt::black << Qt::white << Qt::magenta << Qt::gray
            << Qt::cyan << Qt::red << Qt::blue << Qt::yellow << Qt::green
            << Qt::darkMagenta << Qt::darkCyan << Qt::darkRed << Qt::darkBlue
            << Qt::darkYellow << Qt::darkGreen << Qt::darkGray;

    QStringList names;
    names << tr("Black") << tr("White") << tr("Magenta") << tr("Gray")
          << tr("Cyan") << tr("Red") << tr("Blue") << tr("Yellow")
          << tr("Green") << tr("Dark Magenta") << tr("Dark Cyan")
          << tr("Dark Red") << tr("Dark Blue") << tr("Dark Yellow")
          << tr("Dark Green") << tr("Dark Gray") ;

    QMenu *colorMenu = new QMenu;
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()),
                this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor) {
            colorMenu->setDefaultAction(action);
        }
    }
    return colorMenu;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile,
                        QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    QRect target(0, 0, 50, 60);
    QRect source(0, 0, 42, 42);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

int MainWindow::newDiagram(QString filePath)
{  
    saveIfNeeded();
    undoList.clear();
    redoList.clear();
    scene->cleanScene();    
    libraryList.clear(); //or set defaults
    buttonIdByName.clear();//or set defaults
    scene->setLibList(libraryList);
    updateLibraries();
    myFilePath="";
    setDefaultOptions();

    if(filePath=="")    
        return 0;    

    myFilePath=filePath;
    if(!scene->fromXmlFormat(parseDocument(myFilePath)))
        newDiagram();

    return 1;
}

QDomDocument MainWindow::parseDocument(QString filePath)
{    
    QDomDocument document;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        bool parsing=document.setContent(&file);
        file.close();
        if(!parsing)
        {
            QMessageBox::warning(this,"Parsing warning","Invalid or void "
                                 " element found in file.");
        }        
    }
    else
        QMessageBox::critical(this,"Error","Could not open file for read.");

    return document;
}



int MainWindow::saveIfNeeded()
{
    if(myFilePath!="" || scene->items().count()>0)
    {}//TODO save opened or modified diagram
    return 0;
}

int MainWindow::openDiagram()
{
    QString
    filePath = QFileDialog::getOpenFileName(this,"Open",
               currentDir(),"Diagram for SIE code generator (*.sie)");

    if(filePath.isEmpty())
        return 0;

    if(!QFileInfo(filePath).isReadable())
    {
        QMessageBox::critical(this,"Error","File is not readable "
                                           " or not exists.");
        return 0;
    }

    newDiagram(filePath);
    return 0;
}

int MainWindow::saveDiagram()
{
    if(myFilePath=="")
    {
        saveAsDiagram();
        return 0;
    }
    if(!QFileInfo(myFilePath).isWritable() && QFileInfo(myFilePath).exists())
    {
        QMessageBox::critical(this,"Error","File is not writable.");
        return 0;
    }
    QFile file(myFilePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        scene->setLibList(libraryList);
        QDomDocument document = scene->toXmlFormat();
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << document.toString(4);
        file.close();
        return 1;
    }
    else
        QMessageBox::critical(this,"Error","Could not open file for write.");
    return 0;
}

int MainWindow::saveAsDiagram()
{
    QString filePath = QFileDialog::getSaveFileName(this,"Save as...",
                 currentDir(),"Diagram for SIE code generator (*.sie)");

    if(!filePath.isEmpty())
    {
        myFilePath = filePath;
        saveDiagram();
        return 1;
    }
    return 0;
}

int MainWindow::exportDiagram()
{
    QString picturePath =   QFileDialog::getSaveFileName(this,"Export",
                            currentDir(),"Portable Network Graphics (*.png)");

    if(picturePath.isEmpty()) return 0;

    if(!QFileInfo(picturePath).isWritable() && QFileInfo(picturePath).exists())
    {
        QMessageBox::critical(this,"Error","File is not writable.");
        return 0;
    }
    scene->setDawGrid(0);
    QSize sizeScene= scene->sceneRect().size().toSize();
    QImage img(sizeScene,QImage::Format_ARGB32_Premultiplied);
    QPainter p(&img);
    scene->render(&p,
                  scene->sceneRect(),
                  scene->itemsBoundingRect(),
                  Qt::KeepAspectRatio);
    p.end();
    img.save(picturePath, "png");    
    scene->setDawGrid(gridButton->isChecked()); //TODO : set correct value
    return 1;
}

int MainWindow::libraryForm()
{
    if(!libDialog)
        createLibraryDialog();
    libDialog->setModal(1);
    libUi->listLib->clear();
    libUi->listLib->addItems(libraryList);
    libDialog->setWindowTitle(tr("Library paths..."));
    QStringList oldLibraryList=libraryList;
    libDialog->exec();

    if (libDialog->result() == QDialog::Rejected)
        libraryList = oldLibraryList;
    else
    {
        scene->setLibList(libraryList);
        QDomDocument backUp = scene->toXmlFormat();
        updateLibraries();
        scene->cleanScene();
        scene->fromXmlFormat(backUp);
    } 
    libDialog->close();
    return 0;
}

void MainWindow::createLibraryDialog()
{
    libDialog = new QDialog(this);
    libUi = new Ui_libraryDialog;
    libUi->setupUi(libDialog);

    connect(libUi->addLib,SIGNAL(clicked()),this,SLOT(addLibPath()));
    connect(libUi->delLib,SIGNAL(clicked()),this,SLOT(delLibPath()));
    connect(libUi->editLib,SIGNAL(clicked()),this,SLOT(editLibPath()));
    connect(libUi->upLib,SIGNAL(clicked()),this,SLOT(upLibPath()));
    connect(libUi->downLib,SIGNAL(clicked()),this,SLOT(downLibPath()));
}

int MainWindow::codeForm()
{
    if(!cgDialog)
    {
        createCgDialog();     
    }    
    cgDialog->show(); cgDialog->show(); //Dummy    
    return 0;
}

void MainWindow::createCgDialog()
{
    cgDialog = new QMainWindow(this);
    cgUi = new Ui_codeDialog;
    cgUi->setupUi(cgDialog);
    connect(cgUi->updateButton,SIGNAL(clicked()),this,SLOT(cgGroupClicked()));
    connect(cgUi->compileButton,SIGNAL(clicked()),this,SLOT(executeCompile()));
    connect(cgUi->connectButton,SIGNAL(clicked()),this,SLOT(executeSSH()));
    connect(cgUi->sendButton,SIGNAL(clicked()),this,SLOT(sendCommand()));
    connect(cgUi->commandEdit,SIGNAL(returnPressed()),this,SLOT(sendCommand()));
    connect(cgUi->fpgaButton,SIGNAL(clicked()),this,SLOT(configFPGA()));
    connect(cgUi->exeButton,SIGNAL(clicked()),this,SLOT(exeOnSie()));
    connect(cgUi->saveButton,SIGNAL(clicked()),this,SLOT(saveTemplates()));
    connect(cgUi->killButton,SIGNAL(clicked()),this,SLOT(killProcess()));
    connect(cgUi->lcdOnButton,SIGNAL(clicked()),this,SLOT(lcdOn()));
    connect(cgUi->lcdOffButton,SIGNAL(clicked()),this,SLOT(lcdOff()));

    cgDialog->setWindowTitle(tr("Code Generator..."));
    cgUi->codeTextEdit->setAcceptRichText(true);
    cgUi->logTextEdit->setAcceptRichText(true);
    cgUi->compileTextEdit->setAcceptRichText(true);
    cgUi->sshTextEdit->setAcceptRichText(true);
    cgUi->logTextEdit->setReadOnly(true);
    cgUi->compileTextEdit->setReadOnly(true);
    cgUi->sshTextEdit->setReadOnly(true);
}

void MainWindow::addLibPath()
{    
    QString
    filePath = QFileDialog::getOpenFileName(this,"Open",
               currentDir(),"Custom block for SIE code generator (*.die)");

    if(filePath.isEmpty())
        return;

    if(!QFileInfo(filePath).isReadable())
    {
        QMessageBox::critical(this,"Error","File is not readable "
                                           " or not exists.");
        return;
    }
    QDir myCurrentDir = this->currentDir();
    QString relativePath= myCurrentDir.relativeFilePath(filePath);
    if(libUi->listLib->findItems(relativePath,Qt::MatchExactly).count()==0)
    {               
        libraryList.append(relativePath);
        libUi->listLib->addItem(relativePath);
    }
    else
        QMessageBox::information(this,"Information","Library already exist.");
}

void MainWindow::delLibPath()
{
    QList<QListWidgetItem *> selected = libUi->listLib->selectedItems();
    if(selected.count()>0)
    {        
        libraryList.removeOne(selected.at(0)->text());
        libUi->listLib->clear();
        libUi->listLib->addItems(libraryList);
    }
}

void MainWindow::editLibPath()
{
    QList<QListWidgetItem *> selected = libUi->listLib->selectedItems();
    if(selected.count()>0)
    {        
        QEventLoop waitToFinish;
        callApp *openBlockEditor = new callApp(
                tr("block_editor/blockeditor ") + selected.at(0)->text());
        connect(openBlockEditor, SIGNAL(appClosed()),
                &waitToFinish, SLOT(quit()));
        libDialog->setEnabled(false);
        waitToFinish.exec();
        libDialog->setEnabled(true);
        openBlockEditor->deleteProcess();
        openBlockEditor->deleteLater();
    }
}

void MainWindow::upLibPath()
{
    QList<QListWidgetItem *> selected = libUi->listLib->selectedItems();
    if(selected.count()>0)
    {
        int idx = libraryList.indexOf(selected.first()->text());
        if(idx>0)
        {
            libraryList.move(idx,idx-1);
            libUi->listLib->clear();
            libUi->listLib->addItems(libraryList);
            libUi->listLib->setCurrentRow(idx-1);
        }
    }
}

void MainWindow::downLibPath()
{
    QList<QListWidgetItem *> selected = libUi->listLib->selectedItems();
    if(selected.count()>0)
    {
        int idx = libraryList.indexOf(selected.first()->text());
        if(idx<libraryList.count())
        {
            libraryList.move(idx,idx+1);
            libUi->listLib->clear();
            libUi->listLib->addItems(libraryList);
            libUi->listLib->setCurrentRow(idx+1);
        }
    }
}


int MainWindow::updateLibraries()
{    
    // TODO: the update lib generate segmentartion fault on CG process
    //       update the DomElement of each block is needed.
    libraryList=scene->getLibList();
    createToolBox();
    return 0;
}


int MainWindow::optionsForm()
{
    if(!optionsDialog)
        createOptionsDialog();
    optionsDialog->setModal(1);
    optUi->templateDir->setText(templateDir);
    optUi->templateFile->setText(templateFile);
    optUi->makeFile->setText(makeFile);
    optUi->workDir->setText(workDir);
    optUi->executableFile->setText(executableFile);
    optUi->mipsToolChainDir->setText(mipsToolChainDir);
    optUi->mipsToolChain->setText(mipsToolChain);
    optUi->sieWorkDir->setText(sieWorkDir);
    optUi->fpgaFile->setText(fpgaFile);
    optUi->sieIP->setText(sieIP);
    optUi->configApp->setText(configApp);
    optionsDialog->exec();
    if(optionsDialog->result() == QDialog::Accepted)
    {        
        templateDir = optUi->templateDir->text();
        templateFile = optUi->templateFile->text();
        makeFile = optUi->makeFile->text();
        workDir = optUi->workDir->text();
        executableFile = optUi->executableFile->text();
        mipsToolChainDir = optUi->mipsToolChainDir->text();
        mipsToolChain = optUi->mipsToolChain->text();
        sieWorkDir = optUi->sieWorkDir->text();
        fpgaFile = optUi->fpgaFile->text();
        sieIP = optUi->sieIP->text();
        configApp = optUi->configApp->text();
    }
    optionsDialog->close();
    return 0;
}

void MainWindow::createOptionsDialog()
{
    optionsDialog = new QDialog(this);
    optUi = new Ui_optionsDialog;
    optUi->setupUi(optionsDialog);
    connect(optUi->templateButton,SIGNAL(clicked()),SLOT(editTemplateDir()));
    connect(optUi->workButton,SIGNAL(clicked()),SLOT(editWorkDir()));
    connect(optUi->fpgaButton,SIGNAL(clicked()),SLOT(editFPGABinary()));
    connect(optUi->toolchainButton,SIGNAL(clicked()),this,SLOT(editToolChain()));
}

void MainWindow::editToolChain()
{
    QString
            filePath = QFileDialog::getExistingDirectory(this,
                "Select the toolchain directory...",
                optUi->mipsToolChainDir->text());

    if(filePath.isEmpty())
        return;

    QDir myCurrentDir = this->currentDir();
    QString relativePath= myCurrentDir.relativeFilePath(filePath);
    optUi->mipsToolChainDir->setText(relativePath);
}

void MainWindow::editTemplateDir()
{    
    QString
            filePath = QFileDialog::getExistingDirectory(this,
                "Select the template directory",
                optUi->templateDir->text());

    if(filePath.isEmpty())
        return;

    QDir myCurrentDir = this->currentDir();
    QString relativePath= myCurrentDir.relativeFilePath(filePath);
    optUi->templateDir->setText(relativePath);
}


void MainWindow::editWorkDir()
{
    QString
            filePath = QFileDialog::getExistingDirectory(this,
                "Select the work directory",
                optUi->workDir->text());

    if(filePath.isEmpty())
        return;

    QDir myCurrentDir = this->currentDir();
    QString relativePath= myCurrentDir.relativeFilePath(filePath);
    optUi->workDir->setText(relativePath);
}

void MainWindow::editFPGABinary()
{
    QString
    filePath = QFileDialog::getOpenFileName(this,
                "Select the FPGA binary file",
                optUi->fpgaFile->text(),
                "Binary file for SIE FPGA (*.bit)");

    if(filePath.isEmpty())
        return;

    if(!QFileInfo(filePath).isReadable())
    {
        QMessageBox::critical(this,"Error","File is not readable "
                                           " or not exists.");
        return;
    }

    QDir myCurrentDir = this->currentDir();
    QString relativePath= myCurrentDir.relativeFilePath(filePath);
    optUi->fpgaFile->setText(relativePath);
}

QString MainWindow::callexternapp(QString xexecFile, QString xexecParm)
{
    QEventLoop cxaw;
    callexternappT cxat;
    connect(&cxat, SIGNAL(finished()), &cxaw, SLOT(quit()));
    cxat.execFile = xexecFile;
    cxat.execParm = xexecParm;
    cxat.start();
    cxaw.exec();
    return cxat.retnValu;
}

void MainWindow::finishSSH()
{
    if(sieSSH!=0)
        sieSSH->deleteProcess();
    sieSSH->deleteLater();
    sieSSH=0;
    sshReady=0;
    cgUi->exeButton->setEnabled(false);
    cgUi->fpgaButton->setEnabled(false);
    cgUi->sendButton->setEnabled(false);
    cgUi->commandEdit->setEnabled(false);
    cgUi->killButton->setEnabled(false);
    cgUi->lcdOnButton->setEnabled(false);
    cgUi->lcdOffButton->setEnabled(false);
    cgUi->connectButton->setText("Init SS&H on SIE");
    cgUi->logTextEdit->append(tr("SSH process killed"));   
    cgUi->outputsTab->setCurrentIndex(0);
}

void MainWindow::executeSSH()
{
    if(sieSSH!=0)
        finishSSH();
    sieSSH = new callApp(tr("ssh root@") + sieIP);
    connect(sieSSH,SIGNAL(newData()),this,SLOT(readSSH()));
    connect(sieSSH,SIGNAL(appClosed()),this,SLOT(finishSSH()));
    cgUi->logTextEdit->append(tr("Executing command:  ") +
                              tr("ssh root@") + sieIP);
    cgUi->logTextEdit->append(tr("WARNING*** You have to configure SIE Ethernet"
                                 " Gadget connection previously (USB0)."));
    cgUi->outputsTab->setCurrentIndex(2);   
    sshReady=0;
    cgUi->connectButton->setText("Connecting...");
}

void MainWindow::readSSH()
{
    if(sieSSH!=0)
    {
        QString newData = sieSSH->readData();
        cgUi->sshTextEdit->append(newData);
        //TODO: Another better metode to detect ssh terminal ready?
        if(newData.contains("|__| W I R E L E S S   F R E E D O M"))
        {
            sshReady=1;
            cgUi->logTextEdit->append(tr("Creating work directory on SIE"));
            writeSSH(tr("mkdir ") + sieWorkDir + "\n");
            writeSSH(tr("mkdir ") + sieWorkDir +
                              "/" +executableFile + "/ \n");
            //TODO: find another better metode to mkdir!
            QString command = tr("cd ") + sieWorkDir + tr("/") +
                              executableFile + tr("/");
            writeSSH("echo \"root@host: "+command+tr("\"\n"));
            writeSSH(command + tr("\n"));
            cgUi->exeButton->setEnabled(true);
            cgUi->fpgaButton->setEnabled(true);
            cgUi->sendButton->setEnabled(true);
            cgUi->commandEdit->setEnabled(true);
            cgUi->killButton->setEnabled(true);
            cgUi->lcdOnButton->setEnabled(true);
            cgUi->lcdOffButton->setEnabled(true);
            cgUi->connectButton->setText("Stop SS&H on SIE");
        } else if(newData.contains("s password:"))
        {
            writeSSH(tr("\n"));
        }
    }
}

void MainWindow::sendCommand()
{    
    writeSSH("echo \"root@host: "+cgUi->commandEdit->text()+tr("\"\n"));
    writeSSH(cgUi->commandEdit->text()+tr(" &\n"));
    cgUi->commandEdit->setText("");
}

void MainWindow::writeSSH(QString data)
{
    if(sieSSH!=0)        
        sieSSH->writeData(data);        
}

void MainWindow::finishCompile()
{
    if(compile!=0)
        compile->deleteProcess();
    compile->deleteLater();
    compile=0;
    cgUi->compileButton->setEnabled(true);
}

void MainWindow::executeCompile()
{
    if(compile!=0)
        finishCompile();
    QString tempWorkDir = workDir+"/"+executableFile+"/";
    QString command =
            tr("make -C ") + tempWorkDir + tr(" -f ") + makeFile + " clean";
    cgUi->logTextEdit->append(tr("Executing command:  ") + command );
    compile = new callApp(command);
    usleep(1000000); //1s delay
    command = tr("make -C ") + tempWorkDir + tr(" -f ") + makeFile;
    cgUi->logTextEdit->append(tr("Executing command:  ") + command );
    compile = new callApp(command);
    connect(compile,SIGNAL(newData()),this,SLOT(readCompile()));
    connect(compile,SIGNAL(appClosed()),this,SLOT(finishCompile()));
    cgUi->compileButton->setEnabled(false);
    cgUi->outputsTab->setCurrentIndex(1);
}

void MainWindow::readCompile()
{
    if(compile!=0)
        cgUi->compileTextEdit->append(compile->readData());
}

void MainWindow::configFPGA()
{
    QString tempFPGAFile = fpgaFile;
    cgUi->logTextEdit->append(tr("WARNING*** Make sure before that the "
                                 "SIE processor is not too loaded."));
    cgUi->fpgaButton->setEnabled(false);
    cgUi->connectButton->setEnabled(false);
    cgUi->exeButton->setEnabled(false);
    cgUi->fpgaButton->setText("Configuring...");
    if(!copyFileToSie(tempFPGAFile))
    {
        cgUi->logTextEdit->append(tr("ERROR*** FPGA binary file could not "
                                     "be found. Make sure that this file {") +
                                  tempFPGAFile + tr("} exists."));
        cgUi->outputsTab->setCurrentIndex(0);
    }
    else
    {
        cgUi->logTextEdit->append(tr("Programming FPGA with file ")
                                  + tempFPGAFile );
        QString configCommand = configApp;
        configCommand=configCommand.replace("$FPGA_BINARY",
                      QFileInfo(fpgaFile).fileName());
        writeSSH("echo \"root@host: "+configCommand+tr("\"\n"));
        writeSSH(configCommand + tr("\n"));
        cgUi->outputsTab->setCurrentIndex(2);
    }
    cgUi->fpgaButton->setEnabled(true);
    cgUi->connectButton->setEnabled(true);
    cgUi->exeButton->setEnabled(true);
    cgUi->fpgaButton->setText("Configure &FPGA");    
}

int MainWindow::copyFileToSie(QString filepath)
{

    if(QFileInfo(filepath).exists())
    {
        QEventLoop waitToFinish;
        cgUi->logTextEdit->append(tr("Executing command:  ") +
                                  tr("scp ") + filepath + tr(" root@") +
                                  sieIP + tr(":") + sieWorkDir +
                                  "/"+executableFile + "/");

        callApp copyFile(tr("scp ") + filepath + tr(" root@") + sieIP +
                         tr(":") + sieWorkDir + "/" + executableFile + "/");

        connect(&copyFile, SIGNAL(appClosed()), &waitToFinish, SLOT(quit()));
        waitToFinish.exec();
        cgUi->logTextEdit->append(copyFile.readData());
        copyFile.deleteProcess();
        return 1;
    }
    return 0;
}

void MainWindow::exeOnSie()
{
    QString tempSieApp = workDir + "/" + executableFile + "/" + executableFile;

    cgUi->fpgaButton->setEnabled(false);
    cgUi->connectButton->setEnabled(false);
    cgUi->exeButton->setEnabled(false);
    cgUi->exeButton->setText("Running ...");
    killProcess();
    if(!copyFileToSie(tempSieApp))
    {
        cgUi->logTextEdit->append(tr("ERROR*** SIE binary file could not "
                                     "be found.  Make sure that the application"
                                     " was compiled."));
        cgUi->outputsTab->setCurrentIndex(0);
    }
    else
    {
        cgUi->logTextEdit->append(tr("Executing binary file on SIE.")
                                  + tempSieApp );
        QString Command = "./" + executableFile + " &";
        writeSSH("echo \"root@host: "+Command+tr("\"\n"));        
        writeSSH(Command + tr("\n"));
        cgUi->outputsTab->setCurrentIndex(2);
    }
    cgUi->fpgaButton->setEnabled(true);
    cgUi->connectButton->setEnabled(true);
    cgUi->exeButton->setEnabled(true);
    cgUi->exeButton->setText("&Excecute on SIE");
}

void MainWindow::killProcess()
{
    cgUi->logTextEdit->append(tr("Stoping all running process..."));
    writeSSH("killall -9 " + executableFile + tr("\n"));
    usleep(200000); //wait 200ms
}

void MainWindow::lcdOn()
{
    cgUi->logTextEdit->append(tr("Turning On LCD..."));
    writeSSH(tr("echo 0 > /sys/class/graphics/fb0/blank \n"));
    usleep(200000); //wait 200ms
}

void MainWindow::lcdOff()
{
    cgUi->logTextEdit->append(tr("Turning Off LCD..."));
    writeSSH(tr("echo 4 > /sys/class/graphics/fb0/blank \n"));
    usleep(200000); //wait 200ms
}

//TODO: Change list for pointer list for consumption memory reduction

void MainWindow::undoDiagram()
{
    if(!undoList.isEmpty())
    {
        redoList.append(scene->toXmlFormat());
        scene->cleanScene();
        scene->fromXmlFormat(undoList.last());
        undoList.removeLast();
    }
    fflush(stdout);
}


void MainWindow::redoDiagram()
{
    if(!redoList.isEmpty())
    {
        undoList.append(scene->toXmlFormat());
        scene->cleanScene();
        scene->fromXmlFormat(redoList.last());
        redoList.removeLast();
    }
    fflush(stdout);
}

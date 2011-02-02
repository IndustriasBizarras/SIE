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

const int InsertTextButton = 10;

MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();
    statusBar = new QStatusBar(this);

    scene = new DiagramScene(itemMenu,this);
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
        this, SLOT(textInserted(QGraphicsTextItem*)));

    createToolbars();

    /* Create widgets for code editor */
    headerTextEdit = new  QTextEdit;
    headerTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    headerTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);    
    initTextEdit = new  QTextEdit;
    initTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    initTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    blockTextEdit = new  QTextEdit;
    blockTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    blockTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    extraTextEdit = new  QTextEdit;
    extraTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    extraTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    prototypeLabel = new  QLabel;
    prototypeLabel->setText("\nvoid  BLOCK_NAME () {");
    QFont proFont = prototypeLabel->font(); proFont.setBold(true);
    prototypeLabel->setFont(proFont);
    prototypeLabel->setMaximumWidth(1280);
    initLabel = new  QLabel;
    initLabel->setText("Code For Initialization Section Here");
    proFont = initLabel->font(); proFont.setItalic(true);;
    initLabel->setFont(proFont);
    headerLabel = new  QLabel;
    headerLabel->setText("Code For Header Section Here");
    headerLabel->setFont(proFont);
    extraLabel = new  QLabel;
    extraLabel->setText("}\n\nCode For Extra Section Here");
    extraLabel->setFont(proFont);

    /* Create central widget */
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(toolBox,0,0,9,1);
    view = new QGraphicsView(scene);    
    layout->addWidget(view,0,1,1,1);
    layout->addWidget(headerLabel,1,1,1,1);
    layout->addWidget(headerTextEdit,2,1,1,1);
    layout->addWidget(initLabel,3,1,1,1);
    layout->addWidget(initTextEdit,4,1,1,1);
    layout->addWidget(prototypeLabel,5,1,1,1);
    layout->addWidget(blockTextEdit,6,1,1,1);
    layout->addWidget(extraLabel,7,1,1,1);
    layout->addWidget(extraTextEdit,8,1,1,1);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    setWindowTitle(tr("SIE Code Generator (Block Editor)"));
    setUnifiedTitleAndToolBarOnMac(true);    
    myFilePath = "";

    if(QApplication::argc()>1)
        {newDiagram(QString(QApplication::argv()[1]));}
    statusBar->showMessage("Ready...");
    this->setStatusBar(statusBar);
}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems())
    {
        if (item->type() == Arrow::Type) {
           qgraphicsitem_cast<Arrow *>(item)->removeLines();
           scene->removeItem(item);
           if(qgraphicsitem_cast<Arrow *>(item)==scene->myPolygonPath)
               scene->myPolygonPath=0;

           delete(item);
        }
        //If line is deleted then is romoved from the arrow owner
        else if (item->type() == lineItem::Type &&
                 !qgraphicsitem_cast<lineItem *>(item)->itemIsMovable()) {

           qgraphicsitem_cast<lineItem *>(item)->myOwner()->removeLine(
                                    qgraphicsitem_cast<lineItem *>(item));
           qgraphicsitem_cast<lineItem *>(item)->myOwner()->updatePosition();           
           scene->removeItem(item);           
           delete(item);
       }
       else if (item->type() == DiagramTextItem::Type) {
           if(qgraphicsitem_cast<DiagramTextItem *>(item)->styleIO()!=0xFFF)
           {
               scene->removeTextItem(qgraphicsitem_cast
                                     <DiagramTextItem *>(item));
               scene->removeItem(item);
               delete(item);
           }
           updateProt();
       }
    }
}

void MainWindow::textInserted(QGraphicsTextItem*)
{
    buttonGroup->button(selectedButton)->setChecked(false);
    scene->setMode(DiagramScene::MoveItem);
    updateProt();
}

void MainWindow::updateProt()
{
    prototypeLabel->setText(scene->createPrototype());
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::about()
{
    QMessageBox::question(this, tr("About SIE Code Generator"),
                       tr("TODO <b>:)</b>"));
}

QWidget *MainWindow::createToolButton(int ID, QString type, QIcon icon)
{
    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    button->setText(type);
    buttonGroup->addButton(button,ID);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(type), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));

    QGridLayout *layout = new QGridLayout;
    //INPUTS
    int i=0;
    layout->addWidget(createToolButton(128+i,tr("Bool"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("Char"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("Integer"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("Double"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("Float"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("Short"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("Long"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("UChar"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("UInt"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("UShort"),
                      QIcon(":/images/background1.png")),++i,0);
    layout->addWidget(createToolButton(128+i,tr("ULong"),
                      QIcon(":/images/background1.png")),++i,0);



    //OUTPUTS
    i=0;
    layout->addWidget(createToolButton(i,tr("Bool"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("Char"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("Integer"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("Double"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("Float"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("Short"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("Long"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("UChar"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("UInt"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("UShort"),
                      QIcon(":/images/background3.png")),++i,1);
    layout->addWidget(createToolButton(i,tr("ULong"),
                      QIcon(":/images/background3.png")),++i,1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);
    QWidget *ioWidget = new QWidget;
    ioWidget->setLayout(layout);

    layout = new QGridLayout;
    //Labels
    layout->addWidget(createToolButton(256,tr("Label"),
                      QIcon(":/images/background4.png")),0,0);
    //Values
    layout->addWidget(createToolButton(257,tr("Value"),
                      QIcon(":/images/background4.png")),0,1);

    //Polygon
    layout->addWidget(createToolButton(258,tr("Polygon"),
                      QIcon(":/images/background2.png")),1,0);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);
    QWidget *labelWidget = new QWidget;
    labelWidget->setLayout(layout);


    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(labelWidget->sizeHint().width());
    toolBox->addItem(labelWidget, tr("Basic draw"));
    toolBox->addItem(ioWidget, tr("Inputs/Outputs"));

}

void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons)
        {if (buttonGroup->button(id) != button) button->setChecked(false);}
    selectedButton=id;

    if(id==258)
    {   //Polygon edition
        scene->setMode(DiagramScene::EditPolygon);
    } else {
        scene->setMode(DiagramScene::InsertText);
    }

    scene->setTextType(id,buttonGroup->button(id)->text());

}

void MainWindow::createActions()
{

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

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit diagram editor"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
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
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("75%") << tr("100%") << tr("125%") << tr("150%") << tr("175%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(1);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    editToolBar->addWidget(sceneScaleCombo);
}

bool MainWindow::newDiagram(QString filePath)
{  
    saveIfNeeded();
    scene->cleanScene();
    this->headerTextEdit->clear();
    this->initTextEdit->clear();
    this->blockTextEdit->clear();
    this->extraTextEdit->clear();
    prototypeLabel->setText("\nvoid  BLOCK_NAME () {");
    myFilePath="";

    if(filePath=="")
        return 0;

    myFilePath=filePath;
    QFile file(myFilePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDomDocument document;
        bool parsing=document.setContent(&file);
        file.close();
        if(!parsing)
        {
            QMessageBox::warning(this,"Parsing warning","Invalid or void "
                                 " element found in file.");
            return 0;
        }
        scene->fromXmlFormat(document);       
        return 1;
    }
    else
        QMessageBox::critical(this,"Error","Could not open file for read.");

    return 0;

}

void MainWindow::saveIfNeeded()
{
    if(myFilePath!="" || scene->items().count()>0)
    {}//TODO save opened or modified diagram
}

bool MainWindow::openDiagram()
{
    QString
    filePath = QFileDialog::getOpenFileName(this,"Open",
               currentDir(),"Custom item for SIE code generator (*.die)");

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

bool MainWindow::saveDiagram()
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

bool MainWindow::saveAsDiagram()
{
    QString filePath = QFileDialog::getSaveFileName(this,"Save as...",
                 currentDir(),"Custom item for SIE code generator (*.die)");

    if(!filePath.isEmpty())
    {
        myFilePath = filePath;
        saveDiagram();
        return 1;
    }
    return 0;
}

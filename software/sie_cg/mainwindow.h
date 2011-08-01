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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QtXml>
#include <QtGui>
#include <QHash>

#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "lineitem.h"
#include "arrow.h"
#include "ui_librarydialog.h"
#include "ui_codedialog.h"
#include "ui_optionsdialog.h"
#include "callapp.h"

class callApp;
class DiagramScene;
class DiagramTextItem;
class DiagramItem;
class Ui_libraryDialog;
class Ui_cgDialog;
class Ui_optionsDialog;
class callexternappT;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();
   QString filePath() const
       { return myFilePath;}
   QString currentDir() const
   { return QDir::currentPath();}

   int updateLibraries();

   QStatusBar *statusBar;
   void setFontSettings(QFont font);

   // Options
   QString templateDir;
   QString templateFile;
   QString makeFile;
   QString workDir;
   QString executableFile;
   QString mipsToolChain;
   QString mipsToolChainDir;
   QString sieWorkDir;
   QString fpgaFile;
   QString sieIP;
   QString configApp;
   void writeSSH(QString);

   //Undo-Redo
   QList<QDomDocument> undoList;
   QList<QDomDocument> redoList;
   bool dontDelete;

private slots:
    void backgroundButtonGroupClicked(QAbstractButton *button);
    void buttonGroupClicked(int id);
    void cgGroupClicked();
    void deleteItem();
    void pointerGroupClicked(int id);
    void bringToFront();
    void sendToBack();
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void currentFontChanged(const QFont &font);
    void fontSizeChanged(const QString &size);
    void sceneScaleChanged(const QString &scale);
    void textColorChanged();
    void itemColorChanged();
    void lineColorChanged();
    void textButtonTriggered();
    void fillButtonTriggered();
    void lineButtonTriggered();
    void handleFontChange();
    void about();

    int newDiagram(QString pathFile="");
    int openDiagram();
    int saveDiagram();
    int saveAsDiagram();
    int exportDiagram();

    void undoDiagram();
    void redoDiagram();

    void setGridState();

    int libraryForm();
    void addLibPath();
    void delLibPath();
    void editLibPath();
    void downLibPath();
    void upLibPath();

    int optionsForm();
    void editTemplateDir();
    void editWorkDir();
    void editToolChain();
    void editFPGABinary();

    int codeForm();

    void executeSSH();
    void finishSSH();
    void readSSH();
    void sendCommand();

    void executeCompile();
    void finishCompile();
    void readCompile();

    void configFPGA();
    void exeOnSie();

    void saveTemplates();

    void killProcess();
    void lcdOn();
    void lcdOff();

private:
    void cleanDomElementsByName();
    int saveIfNeeded();
    void addLibrariesButtons(QGridLayout *layout);
    QDomDocument parseDocument(QString filePath);
    void createLibraryDialog();
    void createCgDialog();
    void createOptionsDialog();
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    void sendTo(bool value);
    QWidget *createBackgroundCellWidget(const QString &text,
                                        const QString &image);
    QWidget *createCellWidget(QString text, QDomElement *customItem);

    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    DiagramScene *scene;
    QGraphicsView *view;

    QAction *newAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *openAction;
    QAction *exportImgAction;

    QAction *exitAction;
    QAction *addAction;
    QAction *deleteAction;

    QAction *libraryAction;
    QAction *optionsAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QAction *undoAction;
    QAction *redoAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *preferencesMenu;
    QMenu *aboutMenu;

    QToolBar *fileToolBar;
    QToolBar *cgToolbar;
    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;    

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *cgGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QToolButton *gridButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;
    QString myFilePath;
    QDialog *libDialog;
    Ui_libraryDialog *libUi;
    QMainWindow *cgDialog;
    Ui_codeDialog *cgUi;
    QDialog *optionsDialog;
    Ui_optionsDialog * optUi;
    QStringList libraryList;
    QHash<QString , QDomElement*> *domElementsByName;
    QHash<QString , int> buttonIdByName;
    static QString callexternapp(QString xexecFile, QString xexecParm);

    void setDefaultOptions(){
         templateDir = "templates/basic";
         templateFile = "main.cpp";
         makeFile = "Makefile";
         workDir = "tmp";
         executableFile = "SIE_APP";
         mipsToolChainDir = "";
         mipsToolChain = "mipsel-openwrt-linux";
         sieWorkDir = "/tmp/CG";
         fpgaFile = "templates/basic/basic.bit";
         sieIP = "192.168.254.101";
         configApp = "xc3sprog  $FPGA_BINARY";
    }

    /* CG */
    QString createPrototype(QList <DiagramTextItem *> &textItems,
                            QList <QString> &ioTypes,
                            QList <QString> &ioNames,
                            QList <QString> &valueNames,
                            QList <QString> &values,
                            QString blockNameID,
                            QList <DiagramTextItem *> &inputs,
                            QList <DiagramTextItem *> &outputs);

    bool itemIsHead(DiagramItem * item);
    bool itemIsEnd(DiagramItem * item);
    QString getIoType(DiagramTextItem * item);
    QString passItem(DiagramItem * item,
                     QList<DiagramItem *> &passItems,
                     QList<Arrow *> &passArrows,
                     QString &headerCode,
                     QString &initCode,
                     QString &blockCode,
                     QString &extraCode,
                     QString &mainCode,
                     QString &iosCode,
                     QString &warnings,
                     QString &errors);

    callApp *sieSSH;
    callApp *compile;
    bool sshReady;
    int copyFileToSie(QString filepath);
    QString appDir;
};

class callexternappT : public QThread
{
public:
    QString execFile;
    QString execParm;
    QString retnValu;
    void run()
    {
        QProcess lnexternapp;
        lnexternapp.start(QString("%1 %2").arg(execFile).arg(execParm));
        lnexternapp.waitForFinished(-1);
        retnValu = QString(lnexternapp.readAll());
    }
};

#endif

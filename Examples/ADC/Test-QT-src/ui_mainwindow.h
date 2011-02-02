/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Oct 31 11:42:44 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <signaldisplay.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Salir;
    QAction *actionA_cerca_de;
    QAction *actionAcerca_de_QT;
    QAction *actionAcerca_de_Qt;
    QWidget *centralWidget;
    SignalDisplay *Graph;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(320, 240);
        action_Salir = new QAction(MainWindow);
        action_Salir->setObjectName(QString::fromUtf8("action_Salir"));
        actionA_cerca_de = new QAction(MainWindow);
        actionA_cerca_de->setObjectName(QString::fromUtf8("actionA_cerca_de"));
        actionAcerca_de_QT = new QAction(MainWindow);
        actionAcerca_de_QT->setObjectName(QString::fromUtf8("actionAcerca_de_QT"));
        actionAcerca_de_Qt = new QAction(MainWindow);
        actionAcerca_de_Qt->setObjectName(QString::fromUtf8("actionAcerca_de_Qt"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Graph = new SignalDisplay(centralWidget);
        Graph->setObjectName(QString::fromUtf8("Graph"));
        Graph->setGeometry(QRect(0, 0, 320, 240));
        Graph->setMinimumSize(QSize(100, 20));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ADC Test", 0, QApplication::UnicodeUTF8));
        action_Salir->setText(QApplication::translate("MainWindow", "&Salir", 0, QApplication::UnicodeUTF8));
        actionA_cerca_de->setText(QApplication::translate("MainWindow", "A&cerca de...", 0, QApplication::UnicodeUTF8));
        actionAcerca_de_QT->setText(QApplication::translate("MainWindow", "Acerca de &QT", 0, QApplication::UnicodeUTF8));
        actionAcerca_de_Qt->setText(QApplication::translate("MainWindow", "Acerca de &Qt...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

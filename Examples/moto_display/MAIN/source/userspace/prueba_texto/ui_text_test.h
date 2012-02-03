/********************************************************************************
** Form generated from reading UI file 'text_test.ui'
**
** Created: Thu Nov 24 17:24:01 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXT_TEST_H
#define UI_TEXT_TEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_text_test
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *text_test)
    {
        if (text_test->objectName().isEmpty())
            text_test->setObjectName(QString::fromUtf8("text_test"));
        text_test->resize(320, 240);
        centralWidget = new QWidget(text_test);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 60, 201, 81));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        text_test->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(text_test);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        text_test->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(text_test);

        QMetaObject::connectSlotsByName(text_test);
    } // setupUi

    void retranslateUi(QMainWindow *text_test)
    {
        text_test->setWindowTitle(QApplication::translate("text_test", "text_test", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("text_test", "Prueba Texto", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class text_test: public Ui_text_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXT_TEST_H

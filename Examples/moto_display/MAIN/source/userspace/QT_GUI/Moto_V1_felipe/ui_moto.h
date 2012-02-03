/********************************************************************************
** Form generated from reading UI file 'moto.ui'
**
** Created: Sun Dec 11 17:57:42 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTO_H
#define UI_MOTO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>
#include "manometer.h"
#include "thermometer.h"

QT_BEGIN_NAMESPACE

class Ui_Moto
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    ManoMeter *manometer;
    ManoMeter *manometer_2;
    ThermoMeter *thermometer;
    QWidget *page_2;
    QLabel *label;

    void setupUi(QMainWindow *Moto)
    {
        if (Moto->objectName().isEmpty())
            Moto->setObjectName(QString::fromUtf8("Moto"));
        Moto->resize(320, 240);
        Moto->setCursor(QCursor(Qt::ArrowCursor));
        centralWidget = new QWidget(Moto);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 321, 241));
        stackedWidget->setCursor(QCursor(Qt::ArrowCursor));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        manometer = new ManoMeter(page);
        manometer->setObjectName(QString::fromUtf8("manometer"));
        manometer->setGeometry(QRect(30, 40, 161, 151));
        manometer->setCursor(QCursor(Qt::ArrowCursor));
        manometer_2 = new ManoMeter(page);
        manometer_2->setObjectName(QString::fromUtf8("manometer_2"));
        manometer_2->setGeometry(QRect(170, 60, 141, 131));
        manometer_2->setCursor(QCursor(Qt::ArrowCursor));
        thermometer = new ThermoMeter(page);
        thermometer->setObjectName(QString::fromUtf8("thermometer"));
        thermometer->setGeometry(QRect(-10, 40, 40, 160));
        thermometer->setCursor(QCursor(Qt::BlankCursor));
        stackedWidget->addWidget(page);
        manometer_2->raise();
        manometer->raise();
        thermometer->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 80, 151, 71));
        QFont font;
        font.setPointSize(40);
        label->setFont(font);
        stackedWidget->addWidget(page_2);
        Moto->setCentralWidget(centralWidget);

        retranslateUi(Moto);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Moto);
    } // setupUi

    void retranslateUi(QMainWindow *Moto)
    {
        Moto->setWindowTitle(QApplication::translate("Moto", "Moto", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        manometer->setToolTip(QApplication::translate("Moto", "Shows the pressure", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        manometer->setWhatsThis(QApplication::translate("Moto", "The bar meter widget displays the pressure attached to it", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        manometer_2->setToolTip(QApplication::translate("Moto", "Shows the pressure", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        manometer_2->setWhatsThis(QApplication::translate("Moto", "The bar meter widget displays the pressure attached to it", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        thermometer->setToolTip(QApplication::translate("Moto", "Shows the pressure", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        thermometer->setWhatsThis(QApplication::translate("Moto", "The bar meter widget displays the pressure attached to it", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("Moto", "HOLA", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Moto: public Ui_Moto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTO_H

/********************************************************************************
** Form generated from reading UI file 'moto_v2.ui'
**
** Created: Mon Jan 30 10:50:28 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTO_V2_H
#define UI_MOTO_V2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QRadioButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "analogwidgets/manometer.h"
#include "qprog.h"

QT_BEGIN_NAMESPACE

class Ui_moto_v2
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *Fondo1;
    QTreeView *treeView;
    QRadioButton *radioButton;
    QWidget *page_2;
    QFrame *Fondo2;
    ManoMeter *speed_meter;
    ManoMeter *rmp_meter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QProg *qprog;
    QProg *qprog_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_5;

    void setupUi(QMainWindow *moto_v2)
    {
        if (moto_v2->objectName().isEmpty())
            moto_v2->setObjectName(QString::fromUtf8("moto_v2"));
        moto_v2->resize(322, 243);
        moto_v2->setCursor(QCursor(Qt::BlankCursor));
        centralWidget = new QWidget(moto_v2);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(-1, -1, 321, 241));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-image: url(:/imagenes/carbon.png);\n"
"}\n"
"QTreeView{\n"
"background:white;\n"
"}\n"
"QLabel{\n"
"background: rgba(100%, 100%, 100%, 0%)\n"
"}"));
        Fondo1 = new QFrame(page);
        Fondo1->setObjectName(QString::fromUtf8("Fondo1"));
        Fondo1->setGeometry(QRect(-1, -1, 331, 251));
        Fondo1->setCursor(QCursor(Qt::BlankCursor));
        Fondo1->setFrameShape(QFrame::StyledPanel);
        Fondo1->setFrameShadow(QFrame::Raised);
        treeView = new QTreeView(Fondo1);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 10, 301, 221));
        treeView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::BlankCursor)));
        radioButton = new QRadioButton(Fondo1);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(0, 230, 116, 22));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-image: url(:/imagenes/carbon.png);\n"
"}"));
        Fondo2 = new QFrame(page_2);
        Fondo2->setObjectName(QString::fromUtf8("Fondo2"));
        Fondo2->setGeometry(QRect(-1, -1, 331, 251));
        Fondo2->setCursor(QCursor(Qt::BlankCursor));
        Fondo2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-image: url(:/imagenes/carbon.png);\n"
"}\n"
"QTreeView{\n"
"background:white;\n"
"}\n"
"QLabel{\n"
"background: rgba(100%, 100%, 100%, 0%)\n"
"}"));
        Fondo2->setFrameShape(QFrame::StyledPanel);
        Fondo2->setFrameShadow(QFrame::Raised);
        speed_meter = new ManoMeter(Fondo2);
        speed_meter->setObjectName(QString::fromUtf8("speed_meter"));
        speed_meter->setGeometry(QRect(0, 60, 211, 201));
        speed_meter->setMaximum(160);
        speed_meter->setNominal(60);
        speed_meter->setCritical(120);
        rmp_meter = new ManoMeter(Fondo2);
        rmp_meter->setObjectName(QString::fromUtf8("rmp_meter"));
        rmp_meter->setGeometry(QRect(180, 120, 161, 141));
        rmp_meter->setMaximum(8);
        rmp_meter->setNominal(4);
        rmp_meter->setCritical(7);
        QFont font;
        font.setPointSize(18);
        rmp_meter->setValueFont(font);
        layoutWidget = new QWidget(Fondo2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 221, 61));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        qprog = new QProg(layoutWidget);
        qprog->setObjectName(QString::fromUtf8("qprog"));
        qprog->setCursor(QCursor(Qt::BlankCursor));
        qprog->setValue(0);
        qprog->setProperty("max", QVariant(100));
        qprog->setProperty("font", QVariant(25));
        qprog->setProperty("numPrec", QVariant(0));

        verticalLayout->addWidget(qprog);

        qprog_2 = new QProg(layoutWidget);
        qprog_2->setObjectName(QString::fromUtf8("qprog_2"));
        qprog_2->setCursor(QCursor(Qt::BlankCursor));
        qprog_2->setValue(0);
        qprog_2->setProperty("max", QVariant(100));
        qprog_2->setProperty("font", QVariant(30));
        qprog_2->setProperty("numPrec", QVariant(0));
        qprog_2->setProperty("color", QVariant(QColor(255, 255, 0)));

        verticalLayout->addWidget(qprog_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(159, 158, 158, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_2->setPalette(palette1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("DejaVu Sans"));
        font2.setBold(true);
        font2.setWeight(75);
        label_2->setFont(font2);
        label_2->setCursor(QCursor(Qt::SizeFDiagCursor));

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        label_3 = new QLabel(Fondo2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(240, 20, 66, 25));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_3->setPalette(palette2);
        label_3->setFont(font2);
        label_3->setCursor(QCursor(Qt::SizeFDiagCursor));
        layoutWidget1 = new QWidget(Fondo2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(190, 90, 131, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        layoutWidget->raise();
        layoutWidget->raise();
        label_3->raise();
        speed_meter->raise();
        rmp_meter->raise();
        stackedWidget->addWidget(page_2);
        moto_v2->setCentralWidget(centralWidget);

        retranslateUi(moto_v2);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(moto_v2);
    } // setupUi

    void retranslateUi(QMainWindow *moto_v2)
    {
        moto_v2->setWindowTitle(QApplication::translate("moto_v2", "moto_v2", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        speed_meter->setToolTip(QApplication::translate("moto_v2", "Shows the pressure", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        speed_meter->setWhatsThis(QApplication::translate("moto_v2", "The bar meter widget displays the pressure attached to it", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        speed_meter->setSuffix(QApplication::translate("moto_v2", "[Km/h]", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rmp_meter->setToolTip(QApplication::translate("moto_v2", "Shows the pressure", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        rmp_meter->setWhatsThis(QApplication::translate("moto_v2", "The bar meter widget displays the pressure attached to it", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        rmp_meter->setSuffix(QApplication::translate("moto_v2", "[RPMx1000]", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        qprog->setToolTip(QApplication::translate("moto_v2", " Progress bar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        qprog->setWhatsThis(QApplication::translate("moto_v2", "Progress bar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        qprog_2->setToolTip(QApplication::translate("moto_v2", " Progress bar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        qprog_2->setWhatsThis(QApplication::translate("moto_v2", "Progress bar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("moto_v2", "BATTERY", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("moto_v2", "FUEL", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("moto_v2", "FUEL", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        label_6->setText(QString());
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class moto_v2: public Ui_moto_v2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTO_V2_H

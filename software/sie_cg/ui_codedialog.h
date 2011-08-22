/********************************************************************************
** Form generated from reading UI file 'codedialog.ui'
**
** Created: Wed Aug 17 14:35:21 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEDIALOG_H
#define UI_CODEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_codeDialog
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *codesTab;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *codeTextEdit;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *makeTextEdit;
    QVBoxLayout *verticalLayout;
    QPushButton *okButton;
    QPushButton *updateButton;
    QPushButton *saveButton;
    QPushButton *compileButton;
    QPushButton *connectButton;
    QPushButton *exeButton;
    QPushButton *fpgaButton;
    QTabWidget *outputsTab;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QTextEdit *logTextEdit;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *compileTextEdit;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *sshTextEdit;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *commandEdit;
    QPushButton *sendButton;
    QPushButton *killButton;
    QPushButton *lcdOnButton;
    QPushButton *lcdOffButton;

    void setupUi(QMainWindow *codeDialog)
    {
        if (codeDialog->objectName().isEmpty())
            codeDialog->setObjectName(QString::fromUtf8("codeDialog"));
        codeDialog->resize(803, 473);
        centralwidget = new QWidget(codeDialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        codesTab = new QTabWidget(centralwidget);
        codesTab->setObjectName(QString::fromUtf8("codesTab"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        codesTab->setFont(font);
        codesTab->setTabPosition(QTabWidget::South);
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_3 = new QVBoxLayout(tab_4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        codeTextEdit = new QTextEdit(tab_4);
        codeTextEdit->setObjectName(QString::fromUtf8("codeTextEdit"));
        codeTextEdit->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(80, 80, 80, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(100, 100, 100, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(40, 40, 40, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(53, 53, 53, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        codeTextEdit->setPalette(palette);
        codeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout_3->addWidget(codeTextEdit);

        codesTab->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_2 = new QVBoxLayout(tab_5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        makeTextEdit = new QTextEdit(tab_5);
        makeTextEdit->setObjectName(QString::fromUtf8("makeTextEdit"));
        makeTextEdit->setMaximumSize(QSize(16777215, 320));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        makeTextEdit->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier New"));
        makeTextEdit->setFont(font1);
        makeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout_2->addWidget(makeTextEdit);

        codesTab->addTab(tab_5, QString());

        horizontalLayout_2->addWidget(codesTab);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        okButton = new QPushButton(centralwidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        verticalLayout->addWidget(okButton);

        updateButton = new QPushButton(centralwidget);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));

        verticalLayout->addWidget(updateButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        verticalLayout->addWidget(saveButton);

        compileButton = new QPushButton(centralwidget);
        compileButton->setObjectName(QString::fromUtf8("compileButton"));

        verticalLayout->addWidget(compileButton);

        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        verticalLayout->addWidget(connectButton);

        exeButton = new QPushButton(centralwidget);
        exeButton->setObjectName(QString::fromUtf8("exeButton"));
        exeButton->setEnabled(false);

        verticalLayout->addWidget(exeButton);

        fpgaButton = new QPushButton(centralwidget);
        fpgaButton->setObjectName(QString::fromUtf8("fpgaButton"));
        fpgaButton->setEnabled(false);

        verticalLayout->addWidget(fpgaButton);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_5->addLayout(horizontalLayout_2);

        outputsTab = new QTabWidget(centralwidget);
        outputsTab->setObjectName(QString::fromUtf8("outputsTab"));
        outputsTab->setEnabled(true);
        outputsTab->setMaximumSize(QSize(16777215, 260));
        outputsTab->setFont(font);
        outputsTab->setLayoutDirection(Qt::LeftToRight);
        outputsTab->setTabPosition(QTabWidget::South);
        outputsTab->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        logTextEdit = new QTextEdit(tab);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));
        logTextEdit->setMaximumSize(QSize(16777215, 200));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        logTextEdit->setPalette(palette2);
        logTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        horizontalLayout->addWidget(logTextEdit);

        outputsTab->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        compileTextEdit = new QTextEdit(tab_2);
        compileTextEdit->setObjectName(QString::fromUtf8("compileTextEdit"));
        compileTextEdit->setMaximumSize(QSize(16777215, 200));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        compileTextEdit->setPalette(palette3);
        compileTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        horizontalLayout_3->addWidget(compileTextEdit);

        outputsTab->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        sshTextEdit = new QTextEdit(tab_3);
        sshTextEdit->setObjectName(QString::fromUtf8("sshTextEdit"));
        sshTextEdit->setMaximumSize(QSize(16777215, 200));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush8(QColor(4, 3, 3, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush8);
        QBrush brush9(QColor(6, 4, 4, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush9);
        QBrush brush10(QColor(5, 3, 3, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Midlight, brush10);
        QBrush brush11(QColor(2, 1, 1, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Dark, brush11);
        QBrush brush12(QColor(2, 2, 2, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Mid, brush12);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush8);
        palette4.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Active, QPalette::AlternateBase, brush11);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette4.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette4.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush11);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
        palette4.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        sshTextEdit->setPalette(palette4);
        sshTextEdit->setFont(font1);
        sshTextEdit->setAutoFillBackground(false);
        sshTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout_4->addWidget(sshTextEdit);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        commandEdit = new QLineEdit(tab_3);
        commandEdit->setObjectName(QString::fromUtf8("commandEdit"));
        commandEdit->setEnabled(false);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush8);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush9);
        palette5.setBrush(QPalette::Active, QPalette::Midlight, brush10);
        palette5.setBrush(QPalette::Active, QPalette::Dark, brush11);
        palette5.setBrush(QPalette::Active, QPalette::Mid, brush12);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush8);
        palette5.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Active, QPalette::AlternateBase, brush11);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette5.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush8);
        palette5.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
        palette5.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        palette5.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush8);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        commandEdit->setPalette(palette5);
        commandEdit->setAutoFillBackground(false);

        horizontalLayout_4->addWidget(commandEdit);

        sendButton = new QPushButton(tab_3);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setEnabled(false);

        horizontalLayout_4->addWidget(sendButton);

        killButton = new QPushButton(tab_3);
        killButton->setObjectName(QString::fromUtf8("killButton"));
        killButton->setEnabled(false);

        horizontalLayout_4->addWidget(killButton);

        lcdOnButton = new QPushButton(tab_3);
        lcdOnButton->setObjectName(QString::fromUtf8("lcdOnButton"));
        lcdOnButton->setEnabled(false);

        horizontalLayout_4->addWidget(lcdOnButton);

        lcdOffButton = new QPushButton(tab_3);
        lcdOffButton->setObjectName(QString::fromUtf8("lcdOffButton"));
        lcdOffButton->setEnabled(false);

        horizontalLayout_4->addWidget(lcdOffButton);


        verticalLayout_4->addLayout(horizontalLayout_4);

        outputsTab->addTab(tab_3, QString());

        verticalLayout_5->addWidget(outputsTab);

        codeDialog->setCentralWidget(centralwidget);

        retranslateUi(codeDialog);
        QObject::connect(okButton, SIGNAL(clicked()), codeDialog, SLOT(hide()));

        codesTab->setCurrentIndex(0);
        outputsTab->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(codeDialog);
    } // setupUi

    void retranslateUi(QMainWindow *codeDialog)
    {
        codeDialog->setWindowTitle(QApplication::translate("codeDialog", "MainWindow", 0, QApplication::UnicodeUTF8));
        codesTab->setTabText(codesTab->indexOf(tab_4), QApplication::translate("codeDialog", "Main code template", 0, QApplication::UnicodeUTF8));
        codesTab->setTabText(codesTab->indexOf(tab_5), QApplication::translate("codeDialog", "Makefile template", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("codeDialog", "C&lose", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        updateButton->setToolTip(QApplication::translate("codeDialog", "Update code from diagram...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        updateButton->setText(QApplication::translate("codeDialog", "&Update", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QApplication::translate("codeDialog", "Save current code to a file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveButton->setText(QApplication::translate("codeDialog", "&Save files ...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        compileButton->setToolTip(QApplication::translate("codeDialog", "Compile current code,,,", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        compileButton->setText(QApplication::translate("codeDialog", "&Compile", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        connectButton->setToolTip(QApplication::translate("codeDialog", "Connect to SIE using SSH", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        connectButton->setText(QApplication::translate("codeDialog", "Init SS&H on SIE", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exeButton->setToolTip(QApplication::translate("codeDialog", "Execute binary on SIE", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        exeButton->setText(QApplication::translate("codeDialog", "&Excecute on SIE", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        fpgaButton->setToolTip(QApplication::translate("codeDialog", "Configure FPGA with predeterminated peripherals...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        fpgaButton->setText(QApplication::translate("codeDialog", "Configure &FPGA", 0, QApplication::UnicodeUTF8));
        outputsTab->setTabText(outputsTab->indexOf(tab), QApplication::translate("codeDialog", "Log", 0, QApplication::UnicodeUTF8));
        outputsTab->setTabText(outputsTab->indexOf(tab_2), QApplication::translate("codeDialog", "Compile output", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("codeDialog", "Sen&d to SIE", 0, QApplication::UnicodeUTF8));
        killButton->setText(QApplication::translate("codeDialog", "Send &Kill", 0, QApplication::UnicodeUTF8));
        lcdOnButton->setText(QApplication::translate("codeDialog", "Send LCD &On", 0, QApplication::UnicodeUTF8));
        lcdOffButton->setText(QApplication::translate("codeDialog", "Send LC&D Off", 0, QApplication::UnicodeUTF8));
        outputsTab->setTabText(outputsTab->indexOf(tab_3), QApplication::translate("codeDialog", "SSH output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class codeDialog: public Ui_codeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEDIALOG_H

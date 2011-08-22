/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created: Wed Aug 17 14:35:21 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optionsDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QLineEdit *templateDir;
    QPushButton *templateButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *templateFile;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QLineEdit *makeFile;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *workDir;
    QPushButton *workButton;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *executableFile;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *fpgaFile;
    QPushButton *fpgaButton;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QLineEdit *mipsToolChainDir;
    QPushButton *toolchainButton;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QLineEdit *mipsToolChain;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *sieWorkDir;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *sieIP;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *configApp;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *optionsDialog)
    {
        if (optionsDialog->objectName().isEmpty())
            optionsDialog->setObjectName(QString::fromUtf8("optionsDialog"));
        optionsDialog->resize(547, 577);
        verticalLayout_2 = new QVBoxLayout(optionsDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(optionsDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(140, 0));

        horizontalLayout_11->addWidget(label_11);

        templateDir = new QLineEdit(tab);
        templateDir->setObjectName(QString::fromUtf8("templateDir"));

        horizontalLayout_11->addWidget(templateDir);

        templateButton = new QPushButton(tab);
        templateButton->setObjectName(QString::fromUtf8("templateButton"));
        templateButton->setMaximumSize(QSize(30, 25));

        horizontalLayout_11->addWidget(templateButton);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(140, 0));

        horizontalLayout->addWidget(label);

        templateFile = new QLineEdit(tab);
        templateFile->setObjectName(QString::fromUtf8("templateFile"));

        horizontalLayout->addWidget(templateFile);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(140, 0));

        horizontalLayout_10->addWidget(label_10);

        makeFile = new QLineEdit(tab);
        makeFile->setObjectName(QString::fromUtf8("makeFile"));

        horizontalLayout_10->addWidget(makeFile);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(140, 0));

        horizontalLayout_2->addWidget(label_2);

        workDir = new QLineEdit(tab);
        workDir->setObjectName(QString::fromUtf8("workDir"));

        horizontalLayout_2->addWidget(workDir);

        workButton = new QPushButton(tab);
        workButton->setObjectName(QString::fromUtf8("workButton"));
        workButton->setMaximumSize(QSize(30, 25));

        horizontalLayout_2->addWidget(workButton);


        verticalLayout->addLayout(horizontalLayout_2);

        line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(140, 0));

        horizontalLayout_3->addWidget(label_3);

        executableFile = new QLineEdit(tab);
        executableFile->setObjectName(QString::fromUtf8("executableFile"));

        horizontalLayout_3->addWidget(executableFile);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(140, 0));

        horizontalLayout_5->addWidget(label_5);

        fpgaFile = new QLineEdit(tab);
        fpgaFile->setObjectName(QString::fromUtf8("fpgaFile"));

        horizontalLayout_5->addWidget(fpgaFile);

        fpgaButton = new QPushButton(tab);
        fpgaButton->setObjectName(QString::fromUtf8("fpgaButton"));
        fpgaButton->setMaximumSize(QSize(30, 25));

        horizontalLayout_5->addWidget(fpgaButton);


        verticalLayout->addLayout(horizontalLayout_5);

        line_3 = new QFrame(tab);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(140, 0));

        horizontalLayout_12->addWidget(label_12);

        mipsToolChainDir = new QLineEdit(tab);
        mipsToolChainDir->setObjectName(QString::fromUtf8("mipsToolChainDir"));

        horizontalLayout_12->addWidget(mipsToolChainDir);

        toolchainButton = new QPushButton(tab);
        toolchainButton->setObjectName(QString::fromUtf8("toolchainButton"));
        toolchainButton->setMaximumSize(QSize(30, 25));

        horizontalLayout_12->addWidget(toolchainButton);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(140, 0));

        horizontalLayout_8->addWidget(label_8);

        mipsToolChain = new QLineEdit(tab);
        mipsToolChain->setObjectName(QString::fromUtf8("mipsToolChain"));

        horizontalLayout_8->addWidget(mipsToolChain);


        verticalLayout->addLayout(horizontalLayout_8);

        line_4 = new QFrame(tab);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(140, 0));

        horizontalLayout_4->addWidget(label_4);

        sieWorkDir = new QLineEdit(tab);
        sieWorkDir->setObjectName(QString::fromUtf8("sieWorkDir"));

        horizontalLayout_4->addWidget(sieWorkDir);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(140, 0));

        horizontalLayout_6->addWidget(label_6);

        sieIP = new QLineEdit(tab);
        sieIP->setObjectName(QString::fromUtf8("sieIP"));

        horizontalLayout_6->addWidget(sieIP);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(140, 0));

        horizontalLayout_7->addWidget(label_7);

        configApp = new QLineEdit(tab);
        configApp->setObjectName(QString::fromUtf8("configApp"));

        horizontalLayout_7->addWidget(configApp);


        verticalLayout->addLayout(horizontalLayout_7);

        tabWidget->addTab(tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_9 = new QLabel(optionsDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_9->addWidget(label_9);

        buttonBox = new QDialogButtonBox(optionsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_9->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_9);


        retranslateUi(optionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), optionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), optionsDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(optionsDialog);
    } // setupUi

    void retranslateUi(QDialog *optionsDialog)
    {
        optionsDialog->setWindowTitle(QApplication::translate("optionsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("optionsDialog", "Template directory", 0, QApplication::UnicodeUTF8));
        templateDir->setText(QApplication::translate("optionsDialog", "templates/basic", 0, QApplication::UnicodeUTF8));
        templateButton->setText(QApplication::translate("optionsDialog", "...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("optionsDialog", "Main code template", 0, QApplication::UnicodeUTF8));
        templateFile->setText(QApplication::translate("optionsDialog", "main.cpp", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("optionsDialog", "Makefile template", 0, QApplication::UnicodeUTF8));
        makeFile->setText(QApplication::translate("optionsDialog", "Makefile", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("optionsDialog", "Local work directory", 0, QApplication::UnicodeUTF8));
        workDir->setText(QApplication::translate("optionsDialog", "tmp", 0, QApplication::UnicodeUTF8));
        workButton->setText(QApplication::translate("optionsDialog", "...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("optionsDialog", "Executable name", 0, QApplication::UnicodeUTF8));
        executableFile->setText(QApplication::translate("optionsDialog", "SIE_APP", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("optionsDialog", "FPGA binary file", 0, QApplication::UnicodeUTF8));
        fpgaFile->setText(QApplication::translate("optionsDialog", "templates/FPGA_binarys/basic.bit", 0, QApplication::UnicodeUTF8));
        fpgaButton->setText(QApplication::translate("optionsDialog", "...", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("optionsDialog", "Toolchain directory", 0, QApplication::UnicodeUTF8));
        mipsToolChainDir->setText(QString());
        toolchainButton->setText(QApplication::translate("optionsDialog", "...", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("optionsDialog", "Toolchain base name", 0, QApplication::UnicodeUTF8));
        mipsToolChain->setText(QApplication::translate("optionsDialog", "mipsel-openwrt-linux", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("optionsDialog", "SIE work directory", 0, QApplication::UnicodeUTF8));
        sieWorkDir->setText(QApplication::translate("optionsDialog", "/tmp/CG", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("optionsDialog", "SIE USB0 ip", 0, QApplication::UnicodeUTF8));
        sieIP->setText(QApplication::translate("optionsDialog", "192.168.254.101", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("optionsDialog", "SIE configuration command", 0, QApplication::UnicodeUTF8));
        configApp->setText(QApplication::translate("optionsDialog", "xcs3prog  $FPGA_BINARY", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("optionsDialog", "General", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("optionsDialog", "Options will be saved when you save your diagram...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class optionsDialog: public Ui_optionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H

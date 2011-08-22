/********************************************************************************
** Form generated from reading UI file 'librarydialog.ui'
**
** Created: Wed Aug 17 14:35:21 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIBRARYDIALOG_H
#define UI_LIBRARYDIALOG_H

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
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_libraryDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QListWidget *listLib;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *addLib;
    QPushButton *editLib;
    QPushButton *delLib;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *upLib;
    QPushButton *downLib;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *libraryDialog)
    {
        if (libraryDialog->objectName().isEmpty())
            libraryDialog->setObjectName(QString::fromUtf8("libraryDialog"));
        libraryDialog->resize(538, 454);
        verticalLayout_4 = new QVBoxLayout(libraryDialog);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listLib = new QListWidget(libraryDialog);
        listLib->setObjectName(QString::fromUtf8("listLib"));

        horizontalLayout->addWidget(listLib);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addLib = new QPushButton(libraryDialog);
        addLib->setObjectName(QString::fromUtf8("addLib"));
        addLib->setMaximumSize(QSize(140, 16777215));

        verticalLayout->addWidget(addLib);

        editLib = new QPushButton(libraryDialog);
        editLib->setObjectName(QString::fromUtf8("editLib"));
        editLib->setMaximumSize(QSize(140, 16777215));

        verticalLayout->addWidget(editLib);

        delLib = new QPushButton(libraryDialog);
        delLib->setObjectName(QString::fromUtf8("delLib"));
        delLib->setMaximumSize(QSize(140, 16777215));

        verticalLayout->addWidget(delLib);


        verticalLayout_3->addLayout(verticalLayout);

        line_2 = new QFrame(libraryDialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        upLib = new QPushButton(libraryDialog);
        upLib->setObjectName(QString::fromUtf8("upLib"));
        upLib->setMaximumSize(QSize(140, 16777215));

        verticalLayout_2->addWidget(upLib);

        downLib = new QPushButton(libraryDialog);
        downLib->setObjectName(QString::fromUtf8("downLib"));
        downLib->setMaximumSize(QSize(140, 16777215));

        verticalLayout_2->addWidget(downLib);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        line = new QFrame(libraryDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_9 = new QLabel(libraryDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_2->addWidget(label_9);

        buttonBox = new QDialogButtonBox(libraryDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout_4->addLayout(horizontalLayout_2);


        retranslateUi(libraryDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), libraryDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), libraryDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(libraryDialog);
    } // setupUi

    void retranslateUi(QDialog *libraryDialog)
    {
        libraryDialog->setWindowTitle(QApplication::translate("libraryDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        addLib->setText(QApplication::translate("libraryDialog", "&Add Library", 0, QApplication::UnicodeUTF8));
        editLib->setText(QApplication::translate("libraryDialog", "&Edit library", 0, QApplication::UnicodeUTF8));
        delLib->setText(QApplication::translate("libraryDialog", "&Remove library", 0, QApplication::UnicodeUTF8));
        upLib->setText(QApplication::translate("libraryDialog", "&Up", 0, QApplication::UnicodeUTF8));
        downLib->setText(QApplication::translate("libraryDialog", "&Down", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("libraryDialog", "Library paths will be saved when you save your diagram...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class libraryDialog: public Ui_libraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIBRARYDIALOG_H

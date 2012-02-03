/********************************************************************************
** Form generated from reading UI file 'patientcare.ui'
**
** Created: Mon Nov 14 21:07:32 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTCARE_H
#define UI_PATIENTCARE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qt5waybutton.h"
#include "qtbasicgraph.h"
#include "qtmultislider.h"
#include "qtscrolldial.h"
#include "qtsvgslideswitch.h"

QT_BEGIN_NAMESPACE

class Ui_PatientCare
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *topLayout;
    QHBoxLayout *layoutGroupBoxes;
    QGroupBox *gbGeneral;
    QVBoxLayout *layoutGeneral;
    QHBoxLayout *horizontalLayout;
    QLabel *lblGeneral;
    QWidget *widget;
    QSpacerItem *verticalSpacer_2;
    QtSvgSlideSwitch *switchSystemOff;
    QLabel *label;
    QtSvgSlideSwitch *switchNightMode;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QGroupBox *gbMedication;
    QVBoxLayout *layoutMedication;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblMedication;
    QWidget *widget2;
    QSpacerItem *spacerMedication1;
    QtScrollDial *medicineFlow;
    QLabel *labelFlow;
    QSpacerItem *spacerMedication2;
    QGroupBox *gbFlow;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblLedFlow;
    QLabel *lblMedicineFlow;
    QWidget *widget_3;
    QLabel *lblStatusFlow;
    QLabel *lblFlow;
    QtMultiSlider *multiSliderMedicine;
    QLabel *lblRangeFlow;
    QGroupBox *gbHeartRate;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblLedHeartRate;
    QLabel *lblHeartRate;
    QWidget *widget_4;
    QLabel *lblStatusHeartRate;
    QLabel *lblRate;
    QtMultiSlider *multiSliderHeartRate;
    QLabel *lblRangePulse;
    QGroupBox *gbGraph;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_12;
    Qt5WayButton *heartRateNavigator;
    QLabel *labelNavigator;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_7;
    QtBasicGraph *heartRatePlot;

    void setupUi(QWidget *PatientCare)
    {
        if (PatientCare->objectName().isEmpty())
            PatientCare->setObjectName(QString::fromUtf8("PatientCare"));
        PatientCare->resize(682, 480);
        QFont font;
        font.setPointSize(7);
        PatientCare->setFont(font);
        verticalLayout_2 = new QVBoxLayout(PatientCare);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(PatientCare);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(5, 0));
        label_4->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(117, 116, 118), stop:1 rgb(60, 57, 61)); color: rgb(255, 255, 255)"));

        horizontalLayout_6->addWidget(label_4);

        label_2 = new QLabel(PatientCare);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(117, 116, 118), stop:1 rgb(60, 57, 61)); color: rgb(255, 255, 255)"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/qt-logo32x32.png")));
        label_2->setMargin(4);
        label_2->setIndent(9);

        horizontalLayout_6->addWidget(label_2);

        label_3 = new QLabel(PatientCare);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sans Serif"));
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(117, 116, 118), stop:1 rgb(60, 57, 61)); color: rgb(255, 255, 255)"));
        label_3->setIndent(5);

        horizontalLayout_6->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout_6);

        topLayout = new QVBoxLayout();
#ifndef Q_OS_MAC
        topLayout->setContentsMargins(9, 9, 9, 9);
#endif
        topLayout->setObjectName(QString::fromUtf8("topLayout"));
        layoutGroupBoxes = new QHBoxLayout();
        layoutGroupBoxes->setObjectName(QString::fromUtf8("layoutGroupBoxes"));
        gbGeneral = new QGroupBox(PatientCare);
        gbGeneral->setObjectName(QString::fromUtf8("gbGeneral"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(gbGeneral->sizePolicy().hasHeightForWidth());
        gbGeneral->setSizePolicy(sizePolicy1);
        gbGeneral->setMinimumSize(QSize(150, 0));
        gbGeneral->setMaximumSize(QSize(150, 16777215));
        QFont font2;
        gbGeneral->setFont(font2);
        gbGeneral->setFlat(false);
        layoutGeneral = new QVBoxLayout(gbGeneral);
        layoutGeneral->setObjectName(QString::fromUtf8("layoutGeneral"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblGeneral = new QLabel(gbGeneral);
        lblGeneral->setObjectName(QString::fromUtf8("lblGeneral"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblGeneral->sizePolicy().hasHeightForWidth());
        lblGeneral->setSizePolicy(sizePolicy2);
        lblGeneral->setMinimumSize(QSize(0, 22));

        horizontalLayout->addWidget(lblGeneral);

        widget = new QWidget(gbGeneral);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        widget->setMaximumSize(QSize(16777215, 2));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(widget);


        layoutGeneral->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        layoutGeneral->addItem(verticalSpacer_2);

        switchSystemOff = new QtSvgSlideSwitch(gbGeneral);
        switchSystemOff->setObjectName(QString::fromUtf8("switchSystemOff"));
        switchSystemOff->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 0)"));

        layoutGeneral->addWidget(switchSystemOff);

        label = new QLabel(gbGeneral);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);
        label->setAlignment(Qt::AlignCenter);

        layoutGeneral->addWidget(label);

        switchNightMode = new QtSvgSlideSwitch(gbGeneral);
        switchNightMode->setObjectName(QString::fromUtf8("switchNightMode"));
        switchNightMode->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 0)"));

        layoutGeneral->addWidget(switchNightMode);

        label_5 = new QLabel(gbGeneral);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy4.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy4);
        label_5->setAlignment(Qt::AlignCenter);

        layoutGeneral->addWidget(label_5);

        verticalSpacer = new QSpacerItem(20, 73, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutGeneral->addItem(verticalSpacer);


        layoutGroupBoxes->addWidget(gbGeneral);

        gbMedication = new QGroupBox(PatientCare);
        gbMedication->setObjectName(QString::fromUtf8("gbMedication"));
        sizePolicy1.setHeightForWidth(gbMedication->sizePolicy().hasHeightForWidth());
        gbMedication->setSizePolicy(sizePolicy1);
        gbMedication->setMinimumSize(QSize(120, 0));
        gbMedication->setMaximumSize(QSize(120, 16777215));
        gbMedication->setFont(font2);
        gbMedication->setFlat(false);
        layoutMedication = new QVBoxLayout(gbMedication);
        layoutMedication->setObjectName(QString::fromUtf8("layoutMedication"));
        layoutMedication->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblMedication = new QLabel(gbMedication);
        lblMedication->setObjectName(QString::fromUtf8("lblMedication"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lblMedication->sizePolicy().hasHeightForWidth());
        lblMedication->setSizePolicy(sizePolicy5);
        lblMedication->setMinimumSize(QSize(0, 22));

        horizontalLayout_2->addWidget(lblMedication);

        widget2 = new QWidget(gbMedication);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        sizePolicy3.setHeightForWidth(widget2->sizePolicy().hasHeightForWidth());
        widget2->setSizePolicy(sizePolicy3);
        widget2->setMaximumSize(QSize(16777215, 2));
        widget2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(widget2);


        layoutMedication->addLayout(horizontalLayout_2);

        spacerMedication1 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        layoutMedication->addItem(spacerMedication1);

        medicineFlow = new QtScrollDial(gbMedication);
        medicineFlow->setObjectName(QString::fromUtf8("medicineFlow"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(medicineFlow->sizePolicy().hasHeightForWidth());
        medicineFlow->setSizePolicy(sizePolicy6);
        medicineFlow->setMinimumSize(QSize(30, 30));
        medicineFlow->setMaximumSize(QSize(156, 126));

        layoutMedication->addWidget(medicineFlow);

        labelFlow = new QLabel(gbMedication);
        labelFlow->setObjectName(QString::fromUtf8("labelFlow"));
        sizePolicy3.setHeightForWidth(labelFlow->sizePolicy().hasHeightForWidth());
        labelFlow->setSizePolicy(sizePolicy3);
        labelFlow->setMinimumSize(QSize(31, 18));
        labelFlow->setFont(font2);
        labelFlow->setAlignment(Qt::AlignCenter);

        layoutMedication->addWidget(labelFlow);

        spacerMedication2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutMedication->addItem(spacerMedication2);


        layoutGroupBoxes->addWidget(gbMedication);

        gbFlow = new QGroupBox(PatientCare);
        gbFlow->setObjectName(QString::fromUtf8("gbFlow"));
        sizePolicy1.setHeightForWidth(gbFlow->sizePolicy().hasHeightForWidth());
        gbFlow->setSizePolicy(sizePolicy1);
        gbFlow->setMinimumSize(QSize(0, 0));
        gbFlow->setFont(font2);
        gbFlow->setFlat(false);
        gridLayout_3 = new QGridLayout(gbFlow);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblLedFlow = new QLabel(gbFlow);
        lblLedFlow->setObjectName(QString::fromUtf8("lblLedFlow"));
        sizePolicy6.setHeightForWidth(lblLedFlow->sizePolicy().hasHeightForWidth());
        lblLedFlow->setSizePolicy(sizePolicy6);
        lblLedFlow->setPixmap(QPixmap(QString::fromUtf8(":/led-green.svg")));

        horizontalLayout_3->addWidget(lblLedFlow);

        lblMedicineFlow = new QLabel(gbFlow);
        lblMedicineFlow->setObjectName(QString::fromUtf8("lblMedicineFlow"));
        sizePolicy5.setHeightForWidth(lblMedicineFlow->sizePolicy().hasHeightForWidth());
        lblMedicineFlow->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(lblMedicineFlow);

        widget_3 = new QWidget(gbFlow);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy3.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy3);
        widget_3->setMaximumSize(QSize(16777215, 2));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(widget_3);

        lblStatusFlow = new QLabel(gbFlow);
        lblStatusFlow->setObjectName(QString::fromUtf8("lblStatusFlow"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(lblStatusFlow->sizePolicy().hasHeightForWidth());
        lblStatusFlow->setSizePolicy(sizePolicy7);
        lblStatusFlow->setFont(font2);

        horizontalLayout_3->addWidget(lblStatusFlow);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 2);

        lblFlow = new QLabel(gbFlow);
        lblFlow->setObjectName(QString::fromUtf8("lblFlow"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(1);
        sizePolicy8.setHeightForWidth(lblFlow->sizePolicy().hasHeightForWidth());
        lblFlow->setSizePolicy(sizePolicy8);
        lblFlow->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lblFlow, 1, 0, 1, 1);

        multiSliderMedicine = new QtMultiSlider(gbFlow);
        multiSliderMedicine->setObjectName(QString::fromUtf8("multiSliderMedicine"));
        sizePolicy8.setHeightForWidth(multiSliderMedicine->sizePolicy().hasHeightForWidth());
        multiSliderMedicine->setSizePolicy(sizePolicy8);
        multiSliderMedicine->setMinimumSize(QSize(20, 30));
        multiSliderMedicine->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 190, 100)"));

        gridLayout_3->addWidget(multiSliderMedicine, 1, 1, 2, 1);

        lblRangeFlow = new QLabel(gbFlow);
        lblRangeFlow->setObjectName(QString::fromUtf8("lblRangeFlow"));
        lblRangeFlow->setWordWrap(true);

        gridLayout_3->addWidget(lblRangeFlow, 2, 0, 1, 1);


        layoutGroupBoxes->addWidget(gbFlow);

        gbHeartRate = new QGroupBox(PatientCare);
        gbHeartRate->setObjectName(QString::fromUtf8("gbHeartRate"));
        sizePolicy1.setHeightForWidth(gbHeartRate->sizePolicy().hasHeightForWidth());
        gbHeartRate->setSizePolicy(sizePolicy1);
        gbHeartRate->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(gbHeartRate);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblLedHeartRate = new QLabel(gbHeartRate);
        lblLedHeartRate->setObjectName(QString::fromUtf8("lblLedHeartRate"));
        sizePolicy6.setHeightForWidth(lblLedHeartRate->sizePolicy().hasHeightForWidth());
        lblLedHeartRate->setSizePolicy(sizePolicy6);
        lblLedHeartRate->setPixmap(QPixmap(QString::fromUtf8(":/led-green.svg")));

        horizontalLayout_4->addWidget(lblLedHeartRate);

        lblHeartRate = new QLabel(gbHeartRate);
        lblHeartRate->setObjectName(QString::fromUtf8("lblHeartRate"));
        sizePolicy5.setHeightForWidth(lblHeartRate->sizePolicy().hasHeightForWidth());
        lblHeartRate->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(lblHeartRate);

        widget_4 = new QWidget(gbHeartRate);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        sizePolicy3.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy3);
        widget_4->setMaximumSize(QSize(16777215, 2));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(widget_4);

        lblStatusHeartRate = new QLabel(gbHeartRate);
        lblStatusHeartRate->setObjectName(QString::fromUtf8("lblStatusHeartRate"));
        sizePolicy7.setHeightForWidth(lblStatusHeartRate->sizePolicy().hasHeightForWidth());
        lblStatusHeartRate->setSizePolicy(sizePolicy7);
        lblStatusHeartRate->setFont(font2);

        horizontalLayout_4->addWidget(lblStatusHeartRate);


        gridLayout_4->addLayout(horizontalLayout_4, 0, 0, 1, 2);

        lblRate = new QLabel(gbHeartRate);
        lblRate->setObjectName(QString::fromUtf8("lblRate"));
        sizePolicy8.setHeightForWidth(lblRate->sizePolicy().hasHeightForWidth());
        lblRate->setSizePolicy(sizePolicy8);
        lblRate->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lblRate, 1, 0, 1, 1);

        multiSliderHeartRate = new QtMultiSlider(gbHeartRate);
        multiSliderHeartRate->setObjectName(QString::fromUtf8("multiSliderHeartRate"));
        sizePolicy8.setHeightForWidth(multiSliderHeartRate->sizePolicy().hasHeightForWidth());
        multiSliderHeartRate->setSizePolicy(sizePolicy8);
        multiSliderHeartRate->setMinimumSize(QSize(20, 30));
        multiSliderHeartRate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 190, 100)"));

        gridLayout_4->addWidget(multiSliderHeartRate, 1, 1, 2, 1);

        lblRangePulse = new QLabel(gbHeartRate);
        lblRangePulse->setObjectName(QString::fromUtf8("lblRangePulse"));
        lblRangePulse->setWordWrap(true);

        gridLayout_4->addWidget(lblRangePulse, 2, 0, 1, 1);


        layoutGroupBoxes->addWidget(gbHeartRate);


        topLayout->addLayout(layoutGroupBoxes);

        gbGraph = new QGroupBox(PatientCare);
        gbGraph->setObjectName(QString::fromUtf8("gbGraph"));
        sizePolicy5.setHeightForWidth(gbGraph->sizePolicy().hasHeightForWidth());
        gbGraph->setSizePolicy(sizePolicy5);
        gbGraph->setFlat(false);
        horizontalLayout_5 = new QHBoxLayout(gbGraph);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_12 = new QLabel(gbGraph);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy9);

        verticalLayout->addWidget(label_12);

        heartRateNavigator = new Qt5WayButton(gbGraph);
        heartRateNavigator->setObjectName(QString::fromUtf8("heartRateNavigator"));
        QSizePolicy sizePolicy10(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(heartRateNavigator->sizePolicy().hasHeightForWidth());
        heartRateNavigator->setSizePolicy(sizePolicy10);
        heartRateNavigator->setMinimumSize(QSize(120, 120));
        heartRateNavigator->setMaximumSize(QSize(120, 120));
        heartRateNavigator->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 100)"));

        verticalLayout->addWidget(heartRateNavigator);

        labelNavigator = new QLabel(gbGraph);
        labelNavigator->setObjectName(QString::fromUtf8("labelNavigator"));
        sizePolicy9.setHeightForWidth(labelNavigator->sizePolicy().hasHeightForWidth());
        labelNavigator->setSizePolicy(sizePolicy9);
        labelNavigator->setMinimumSize(QSize(68, 18));
        labelNavigator->setFont(font2);
        labelNavigator->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelNavigator);


        horizontalLayout_5->addLayout(verticalLayout);

        frame = new QFrame(gbGraph);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy4.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy4);
        frame->setStyleSheet(QString::fromUtf8("border: 1px solid #888888; border-radius: 2px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        horizontalLayout_7 = new QHBoxLayout(frame);
        horizontalLayout_7->setSpacing(1);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(1, 0, 1, 0);
        heartRatePlot = new QtBasicGraph(frame);
        heartRatePlot->setObjectName(QString::fromUtf8("heartRatePlot"));
        QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(heartRatePlot->sizePolicy().hasHeightForWidth());
        heartRatePlot->setSizePolicy(sizePolicy11);
        heartRatePlot->setMaximumSize(QSize(16777215, 160));

        horizontalLayout_7->addWidget(heartRatePlot);


        horizontalLayout_5->addWidget(frame);


        topLayout->addWidget(gbGraph);


        verticalLayout_2->addLayout(topLayout);


        retranslateUi(PatientCare);

        QMetaObject::connectSlotsByName(PatientCare);
    } // setupUi

    void retranslateUi(QWidget *PatientCare)
    {
        PatientCare->setWindowTitle(QApplication::translate("PatientCare", "PatientCare (Demo)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        label_2->setText(QString());
        label_3->setText(QApplication::translate("PatientCare", "Patient: John Doe", 0, QApplication::UnicodeUTF8));
        gbGeneral->setTitle(QString());
        lblGeneral->setText(QApplication::translate("PatientCare", "GENERAL", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PatientCare", "  Medication  ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PatientCare", "  Night Mode  ", 0, QApplication::UnicodeUTF8));
        gbMedication->setTitle(QString());
        lblMedication->setText(QApplication::translate("PatientCare", "MEDICATION", 0, QApplication::UnicodeUTF8));
        labelFlow->setText(QApplication::translate("PatientCare", "Flow", 0, QApplication::UnicodeUTF8));
        gbFlow->setTitle(QString());
        lblLedFlow->setText(QString());
        lblMedicineFlow->setText(QApplication::translate("PatientCare", "MEDICINE", 0, QApplication::UnicodeUTF8));
        lblStatusFlow->setText(QApplication::translate("PatientCare", "LOW", 0, QApplication::UnicodeUTF8));
        lblFlow->setText(QApplication::translate("PatientCare", "Drip Rate\n"
"60 ml/h", 0, QApplication::UnicodeUTF8));
        lblRangeFlow->setText(QApplication::translate("PatientCare", "Safe Range: 40 - 80", 0, QApplication::UnicodeUTF8));
        gbHeartRate->setTitle(QString());
        lblLedHeartRate->setText(QString());
        lblHeartRate->setText(QApplication::translate("PatientCare", "HEART", 0, QApplication::UnicodeUTF8));
        lblStatusHeartRate->setText(QApplication::translate("PatientCare", "LOW", 0, QApplication::UnicodeUTF8));
        lblRate->setText(QApplication::translate("PatientCare", "Pulse\n"
"72", 0, QApplication::UnicodeUTF8));
        lblRangePulse->setText(QApplication::translate("PatientCare", "Safe Range: 60 - 90", 0, QApplication::UnicodeUTF8));
        gbGraph->setTitle(QString());
        label_12->setText(QApplication::translate("PatientCare", "HEART RATE GRAPH", 0, QApplication::UnicodeUTF8));
        labelNavigator->setText(QApplication::translate("PatientCare", "Zoom", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PatientCare: public Ui_PatientCare {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTCARE_H

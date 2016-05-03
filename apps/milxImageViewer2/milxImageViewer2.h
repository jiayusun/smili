/********************************************************************************
** Form generated from reading UI file 'milxImageViewer2.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MILXIMAGEVIEWER2_H
#define MILXIMAGEVIEWER2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_milxImageViewer2
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QVTKWidget *view2;
    QVTKWidget *view3;
    QVTKWidget *view1;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_19;
    QVTKWidget *view4;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QPushButton *pushButton_25;
    QPushButton *pushButton_26;
    QPushButton *pushButton_27;
    QPushButton *pushButton_28;
    QPushButton *pushButton_29;
    QPushButton *pushButton_30;
    QPushButton *pushButton_31;
    QPushButton *pushButton_32;
    QPushButton *pushButton_33;
    QPushButton *pushButton_34;
    QPushButton *pushButton_51;
    QPushButton *pushButton_52;
    QPushButton *pushButton_53;
    QPushButton *pushButton_54;
    QPushButton *pushButton_55;
    QPushButton *pushButton_56;
    QPushButton *pushButton_57;
    QPushButton *pushButton_58;
    QPushButton *pushButton_59;
    QPushButton *pushButton_60;
    QPushButton *pushButton_61;
    QPushButton *pushButton_62;
    QPushButton *pushButton_63;
    QPushButton *pushButton_64;
    QPushButton *pushButton_65;
    QPushButton *pushButton_66;
    QPushButton *pushButton_67;
    QPushButton *pushButton_68;
    QPushButton *pushButton_69;
    QPushButton *pushButton_70;
    QPushButton *pushButton_36;
    QPushButton *pushButton_37;
    QPushButton *pushButton_38;
    QPushButton *pushButton_39;
    QPushButton *pushButton_71;
    QPushButton *pushButton_72;
    QPushButton *pushButton_73;
    QPushButton *pushButton_74;
    QPushButton *pushButton_75;
    QPushButton *pushButton_76;
    QPushButton *pushButton_77;
    QPushButton *pushButton_78;
    QPushButton *pushButton_79;
    QPushButton *pushButton_81;
    QPushButton *pushButton_82;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QMainWindow *milxImageViewer2)
    {
        if (milxImageViewer2->objectName().isEmpty())
            milxImageViewer2->setObjectName(QString::fromUtf8("milxImageViewer2"));
        milxImageViewer2->resize(920, 683);
        milxImageViewer2->setIconSize(QSize(22, 22));
        actionOpenFile = new QAction(milxImageViewer2);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon);
        actionExit = new QAction(milxImageViewer2);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../Users/Jiayu Sun/.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionPrint = new QAction(milxImageViewer2);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon2);
        actionHelp = new QAction(milxImageViewer2);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon3);
        actionSave = new QAction(milxImageViewer2);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        centralwidget = new QWidget(milxImageViewer2);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(110, 30, 591, 531));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        view2 = new QVTKWidget(gridLayoutWidget);
        view2->setObjectName(QString::fromUtf8("view2"));

        gridLayout_2->addWidget(view2, 1, 0, 1, 1);

        view3 = new QVTKWidget(gridLayoutWidget);
        view3->setObjectName(QString::fromUtf8("view3"));

        gridLayout_2->addWidget(view3, 1, 1, 1, 1);

        view1 = new QVTKWidget(gridLayoutWidget);
        view1->setObjectName(QString::fromUtf8("view1"));

        gridLayout_2->addWidget(view1, 0, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(890, 30, 20, 20));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(890, 50, 20, 20));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(890, 70, 20, 20));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(890, 90, 20, 20));
        pushButton_4->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_19 = new QPushButton(centralwidget);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(700, 30, 71, 23));
        pushButton_19->setStyleSheet(QString::fromUtf8(""));
        view4 = new QVTKWidget(centralwidget);
        view4->setObjectName(QString::fromUtf8("view4"));
        view4->setGeometry(QRect(410, 30, 291, 262));
        pushButton_20 = new QPushButton(centralwidget);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(700, 50, 71, 23));
        pushButton_21 = new QPushButton(centralwidget);
        pushButton_21->setObjectName(QString::fromUtf8("pushButton_21"));
        pushButton_21->setGeometry(QRect(700, 70, 71, 23));
        pushButton_22 = new QPushButton(centralwidget);
        pushButton_22->setObjectName(QString::fromUtf8("pushButton_22"));
        pushButton_22->setGeometry(QRect(700, 90, 71, 23));
        pushButton_23 = new QPushButton(centralwidget);
        pushButton_23->setObjectName(QString::fromUtf8("pushButton_23"));
        pushButton_23->setGeometry(QRect(700, 360, 71, 23));
        pushButton_24 = new QPushButton(centralwidget);
        pushButton_24->setObjectName(QString::fromUtf8("pushButton_24"));
        pushButton_24->setGeometry(QRect(700, 340, 71, 23));
        pushButton_25 = new QPushButton(centralwidget);
        pushButton_25->setObjectName(QString::fromUtf8("pushButton_25"));
        pushButton_25->setGeometry(QRect(700, 320, 71, 23));
        pushButton_26 = new QPushButton(centralwidget);
        pushButton_26->setObjectName(QString::fromUtf8("pushButton_26"));
        pushButton_26->setGeometry(QRect(700, 300, 71, 23));
        pushButton_27 = new QPushButton(centralwidget);
        pushButton_27->setObjectName(QString::fromUtf8("pushButton_27"));
        pushButton_27->setGeometry(QRect(40, 50, 71, 23));
        pushButton_28 = new QPushButton(centralwidget);
        pushButton_28->setObjectName(QString::fromUtf8("pushButton_28"));
        pushButton_28->setGeometry(QRect(40, 70, 71, 23));
        pushButton_29 = new QPushButton(centralwidget);
        pushButton_29->setObjectName(QString::fromUtf8("pushButton_29"));
        pushButton_29->setGeometry(QRect(40, 30, 71, 23));
        pushButton_30 = new QPushButton(centralwidget);
        pushButton_30->setObjectName(QString::fromUtf8("pushButton_30"));
        pushButton_30->setGeometry(QRect(40, 90, 71, 23));
        pushButton_31 = new QPushButton(centralwidget);
        pushButton_31->setObjectName(QString::fromUtf8("pushButton_31"));
        pushButton_31->setGeometry(QRect(40, 360, 71, 23));
        pushButton_32 = new QPushButton(centralwidget);
        pushButton_32->setObjectName(QString::fromUtf8("pushButton_32"));
        pushButton_32->setGeometry(QRect(40, 340, 71, 23));
        pushButton_33 = new QPushButton(centralwidget);
        pushButton_33->setObjectName(QString::fromUtf8("pushButton_33"));
        pushButton_33->setGeometry(QRect(40, 320, 71, 23));
        pushButton_34 = new QPushButton(centralwidget);
        pushButton_34->setObjectName(QString::fromUtf8("pushButton_34"));
        pushButton_34->setGeometry(QRect(40, 300, 71, 23));
        pushButton_51 = new QPushButton(centralwidget);
        pushButton_51->setObjectName(QString::fromUtf8("pushButton_51"));
        pushButton_51->setGeometry(QRect(890, 110, 21, 20));
        pushButton_51->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_52 = new QPushButton(centralwidget);
        pushButton_52->setObjectName(QString::fromUtf8("pushButton_52"));
        pushButton_52->setGeometry(QRect(890, 130, 20, 20));
        pushButton_52->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_53 = new QPushButton(centralwidget);
        pushButton_53->setObjectName(QString::fromUtf8("pushButton_53"));
        pushButton_53->setGeometry(QRect(890, 150, 20, 20));
        pushButton_53->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_54 = new QPushButton(centralwidget);
        pushButton_54->setObjectName(QString::fromUtf8("pushButton_54"));
        pushButton_54->setGeometry(QRect(890, 170, 20, 20));
        pushButton_54->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_55 = new QPushButton(centralwidget);
        pushButton_55->setObjectName(QString::fromUtf8("pushButton_55"));
        pushButton_55->setGeometry(QRect(890, 190, 20, 21));
        pushButton_55->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_56 = new QPushButton(centralwidget);
        pushButton_56->setObjectName(QString::fromUtf8("pushButton_56"));
        pushButton_56->setGeometry(QRect(890, 210, 20, 20));
        pushButton_56->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_57 = new QPushButton(centralwidget);
        pushButton_57->setObjectName(QString::fromUtf8("pushButton_57"));
        pushButton_57->setGeometry(QRect(890, 230, 20, 20));
        pushButton_57->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Icons/help.png);"));
        pushButton_58 = new QPushButton(centralwidget);
        pushButton_58->setObjectName(QString::fromUtf8("pushButton_58"));
        pushButton_58->setGeometry(QRect(890, 270, 20, 20));
        pushButton_58->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_59 = new QPushButton(centralwidget);
        pushButton_59->setObjectName(QString::fromUtf8("pushButton_59"));
        pushButton_59->setGeometry(QRect(890, 290, 20, 20));
        pushButton_59->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_60 = new QPushButton(centralwidget);
        pushButton_60->setObjectName(QString::fromUtf8("pushButton_60"));
        pushButton_60->setGeometry(QRect(890, 350, 20, 20));
        pushButton_60->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_61 = new QPushButton(centralwidget);
        pushButton_61->setObjectName(QString::fromUtf8("pushButton_61"));
        pushButton_61->setGeometry(QRect(890, 370, 20, 20));
        pushButton_61->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_62 = new QPushButton(centralwidget);
        pushButton_62->setObjectName(QString::fromUtf8("pushButton_62"));
        pushButton_62->setGeometry(QRect(890, 250, 20, 20));
        pushButton_62->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_63 = new QPushButton(centralwidget);
        pushButton_63->setObjectName(QString::fromUtf8("pushButton_63"));
        pushButton_63->setGeometry(QRect(890, 310, 20, 20));
        pushButton_63->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_64 = new QPushButton(centralwidget);
        pushButton_64->setObjectName(QString::fromUtf8("pushButton_64"));
        pushButton_64->setGeometry(QRect(890, 330, 20, 20));
        pushButton_64->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_65 = new QPushButton(centralwidget);
        pushButton_65->setObjectName(QString::fromUtf8("pushButton_65"));
        pushButton_65->setGeometry(QRect(890, 390, 20, 20));
        pushButton_65->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_66 = new QPushButton(centralwidget);
        pushButton_66->setObjectName(QString::fromUtf8("pushButton_66"));
        pushButton_66->setGeometry(QRect(890, 430, 20, 20));
        pushButton_66->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_67 = new QPushButton(centralwidget);
        pushButton_67->setObjectName(QString::fromUtf8("pushButton_67"));
        pushButton_67->setGeometry(QRect(890, 410, 20, 20));
        pushButton_67->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_68 = new QPushButton(centralwidget);
        pushButton_68->setObjectName(QString::fromUtf8("pushButton_68"));
        pushButton_68->setGeometry(QRect(890, 450, 20, 20));
        pushButton_68->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_69 = new QPushButton(centralwidget);
        pushButton_69->setObjectName(QString::fromUtf8("pushButton_69"));
        pushButton_69->setGeometry(QRect(890, 470, 20, 20));
        pushButton_69->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_70 = new QPushButton(centralwidget);
        pushButton_70->setObjectName(QString::fromUtf8("pushButton_70"));
        pushButton_70->setGeometry(QRect(890, 490, 20, 20));
        pushButton_70->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_36 = new QPushButton(centralwidget);
        pushButton_36->setObjectName(QString::fromUtf8("pushButton_36"));
        pushButton_36->setGeometry(QRect(890, 510, 20, 20));
        pushButton_36->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_37 = new QPushButton(centralwidget);
        pushButton_37->setObjectName(QString::fromUtf8("pushButton_37"));
        pushButton_37->setGeometry(QRect(60, 660, 20, 20));
        pushButton_37->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_38 = new QPushButton(centralwidget);
        pushButton_38->setObjectName(QString::fromUtf8("pushButton_38"));
        pushButton_38->setGeometry(QRect(90, 660, 20, 20));
        pushButton_38->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_39 = new QPushButton(centralwidget);
        pushButton_39->setObjectName(QString::fromUtf8("pushButton_39"));
        pushButton_39->setGeometry(QRect(120, 660, 21, 20));
        pushButton_39->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_71 = new QPushButton(centralwidget);
        pushButton_71->setObjectName(QString::fromUtf8("pushButton_71"));
        pushButton_71->setGeometry(QRect(150, 660, 21, 20));
        pushButton_71->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_72 = new QPushButton(centralwidget);
        pushButton_72->setObjectName(QString::fromUtf8("pushButton_72"));
        pushButton_72->setGeometry(QRect(180, 660, 20, 20));
        pushButton_72->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_73 = new QPushButton(centralwidget);
        pushButton_73->setObjectName(QString::fromUtf8("pushButton_73"));
        pushButton_73->setGeometry(QRect(210, 660, 20, 20));
        pushButton_73->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_74 = new QPushButton(centralwidget);
        pushButton_74->setObjectName(QString::fromUtf8("pushButton_74"));
        pushButton_74->setGeometry(QRect(240, 660, 20, 20));
        pushButton_74->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_75 = new QPushButton(centralwidget);
        pushButton_75->setObjectName(QString::fromUtf8("pushButton_75"));
        pushButton_75->setGeometry(QRect(270, 660, 20, 20));
        pushButton_75->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_76 = new QPushButton(centralwidget);
        pushButton_76->setObjectName(QString::fromUtf8("pushButton_76"));
        pushButton_76->setGeometry(QRect(300, 660, 20, 20));
        pushButton_76->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_77 = new QPushButton(centralwidget);
        pushButton_77->setObjectName(QString::fromUtf8("pushButton_77"));
        pushButton_77->setGeometry(QRect(330, 660, 20, 20));
        pushButton_77->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_78 = new QPushButton(centralwidget);
        pushButton_78->setObjectName(QString::fromUtf8("pushButton_78"));
        pushButton_78->setGeometry(QRect(420, 660, 20, 20));
        pushButton_78->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_79 = new QPushButton(centralwidget);
        pushButton_79->setObjectName(QString::fromUtf8("pushButton_79"));
        pushButton_79->setGeometry(QRect(750, 540, 20, 20));
        pushButton_79->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_81 = new QPushButton(centralwidget);
        pushButton_81->setObjectName(QString::fromUtf8("pushButton_81"));
        pushButton_81->setGeometry(QRect(390, 660, 20, 20));
        pushButton_81->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        pushButton_82 = new QPushButton(centralwidget);
        pushButton_82->setObjectName(QString::fromUtf8("pushButton_82"));
        pushButton_82->setGeometry(QRect(360, 660, 20, 20));
        pushButton_82->setStyleSheet(QString::fromUtf8("border-image: url(:/Icons/help.png);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(880, 10, 31, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 640, 91, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(790, 540, 61, 21));
        milxImageViewer2->setCentralWidget(centralwidget);

        retranslateUi(milxImageViewer2);

        QMetaObject::connectSlotsByName(milxImageViewer2);
    } // setupUi

    void retranslateUi(QMainWindow *milxImageViewer2)
    {
        milxImageViewer2->setWindowTitle(QApplication::translate("milxImageViewer2", "milxImageViewer2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        milxImageViewer2->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        actionOpenFile->setText(QApplication::translate("milxImageViewer2", "Open File...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("milxImageViewer2", "Exit", 0, QApplication::UnicodeUTF8));
        actionPrint->setText(QApplication::translate("milxImageViewer2", "Print", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("milxImageViewer2", "Help", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("milxImageViewer2", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("milxImageViewer2", "Compare", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_2->setToolTip(QApplication::translate("milxImageViewer2", "Link All Windows", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QApplication::translate("milxImageViewer2", "Switch Window to", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_3->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_4->setToolTip(QApplication::translate("milxImageViewer2", "Import View From", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_4->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_4->setText(QString());
        pushButton_19->setText(QApplication::translate("milxImageViewer2", "Expand", 0, QApplication::UnicodeUTF8));
        pushButton_20->setText(QApplication::translate("milxImageViewer2", "Screenshot", 0, QApplication::UnicodeUTF8));
        pushButton_21->setText(QApplication::translate("milxImageViewer2", "Crosshair", 0, QApplication::UnicodeUTF8));
        pushButton_22->setText(QApplication::translate("milxImageViewer2", "Intensity", 0, QApplication::UnicodeUTF8));
        pushButton_23->setText(QApplication::translate("milxImageViewer2", "Intensity", 0, QApplication::UnicodeUTF8));
        pushButton_24->setText(QApplication::translate("milxImageViewer2", "Crosshair", 0, QApplication::UnicodeUTF8));
        pushButton_25->setText(QApplication::translate("milxImageViewer2", "Screenshot", 0, QApplication::UnicodeUTF8));
        pushButton_26->setText(QApplication::translate("milxImageViewer2", "Expand", 0, QApplication::UnicodeUTF8));
        pushButton_27->setText(QApplication::translate("milxImageViewer2", "Screenshot", 0, QApplication::UnicodeUTF8));
        pushButton_28->setText(QApplication::translate("milxImageViewer2", "Crosshair", 0, QApplication::UnicodeUTF8));
        pushButton_29->setText(QApplication::translate("milxImageViewer2", "Expand", 0, QApplication::UnicodeUTF8));
        pushButton_30->setText(QApplication::translate("milxImageViewer2", "Intensity", 0, QApplication::UnicodeUTF8));
        pushButton_31->setText(QApplication::translate("milxImageViewer2", "Intensity", 0, QApplication::UnicodeUTF8));
        pushButton_32->setText(QApplication::translate("milxImageViewer2", "Crosshair", 0, QApplication::UnicodeUTF8));
        pushButton_33->setText(QApplication::translate("milxImageViewer2", "Screenshot", 0, QApplication::UnicodeUTF8));
        pushButton_34->setText(QApplication::translate("milxImageViewer2", "Expand", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_51->setToolTip(QApplication::translate("milxImageViewer2", "Operations", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_51->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_51->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_52->setToolTip(QApplication::translate("milxImageViewer2", "Thresholds", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_52->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_52->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_53->setToolTip(QApplication::translate("milxImageViewer2", "Transforms", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_53->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_53->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_54->setToolTip(QApplication::translate("milxImageViewer2", "Complex/Vector/4D Imaging", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_54->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_54->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_55->setToolTip(QApplication::translate("milxImageViewer2", "View", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_55->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_55->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_56->setToolTip(QApplication::translate("milxImageViewer2", "Color Maps", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_56->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_56->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_57->setToolTip(QApplication::translate("milxImageViewer2", "Auto-Level Display", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_57->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_57->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_58->setToolTip(QApplication::translate("milxImageViewer2", "Overlay Labelled image as contour from", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_58->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_59->setToolTip(QApplication::translate("milxImageViewer2", "Blend image with", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_59->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_60->setToolTip(QApplication::translate("milxImageViewer2", "Display Histogram", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_60->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_61->setToolTip(QApplication::translate("milxImageViewer2", "Display Slice Surface Plot", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_61->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_62->setToolTip(QApplication::translate("milxImageViewer2", " Overlay Labelled image from", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_62->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_63->setToolTip(QApplication::translate("milxImageViewer2", "Compare as Checkboard to", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_63->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_64->setToolTip(QApplication::translate("milxImageViewer2", "Display as Volume Rendering", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_64->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_65->setToolTip(QApplication::translate("milxImageViewer2", "Display Iso-surface", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_65->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_66->setToolTip(QApplication::translate("milxImageViewer2", "Interpolation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_66->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_67->setToolTip(QApplication::translate("milxImageViewer2", "Image Information", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_67->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_68->setToolTip(QApplication::translate("milxImageViewer2", "Apply Orientation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_68->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_69->setToolTip(QApplication::translate("milxImageViewer2", "Show Cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_69->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_70->setToolTip(QApplication::translate("milxImageViewer2", "Show Human Orientation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_70->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_36->setToolTip(QApplication::translate("milxImageViewer2", "Show Cusor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_36->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_37->setToolTip(QApplication::translate("milxImageViewer2", "Window Properties", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_37->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_38->setToolTip(QApplication::translate("milxImageViewer2", "White Background", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_38->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_39->setToolTip(QApplication::translate("milxImageViewer2", "Axes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_39->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_71->setToolTip(QApplication::translate("milxImageViewer2", "Two-Sided Lighting", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_71->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_72->setToolTip(QApplication::translate("milxImageViewer2", "Draw Line", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_72->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_73->setToolTip(QApplication::translate("milxImageViewer2", "Measure Distance", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_73->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_74->setToolTip(QApplication::translate("milxImageViewer2", "Measure Cross Distance", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_74->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_75->setToolTip(QApplication::translate("milxImageViewer2", "Measure Angle", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_75->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_76->setToolTip(QApplication::translate("milxImageViewer2", "Draw Plane", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_76->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_77->setToolTip(QApplication::translate("milxImageViewer2", "Draw Box/Cuboid", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_77->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_78->setToolTip(QApplication::translate("milxImageViewer2", "Contouring", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_78->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_79->setToolTip(QApplication::translate("milxImageViewer2", "Contouring", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_79->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_81->setToolTip(QApplication::translate("milxImageViewer2", "Insert Text", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_81->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_82->setToolTip(QApplication::translate("milxImageViewer2", "Draw Sphere/Circle", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_82->setText(QString());
        label->setText(QApplication::translate("milxImageViewer2", "Imging", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("milxImageViewer2", "Wndow Properties", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("milxImageViewer2", "Contouring", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class milxImageViewer2: public Ui_milxImageViewer2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MILXIMAGEVIEWER2_H

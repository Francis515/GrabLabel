/********************************************************************************
** Form generated from reading UI file 'GrabLabel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRABLABEL_H
#define UI_GRABLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "imageviewer.h"

QT_BEGIN_NAMESPACE

class Ui_GrabLabelClass
{
public:
    QAction *actionOpenImg;
    QAction *actionSaveGray;
    QAction *actionRGB;
    QAction *actionLoadLabel;
    QAction *actionCloseImg;
    QAction *actionSaveAsGray;
    QAction *actionSaveAsRGB;
    QAction *actionCloseLabel;
    QAction *actionHelp;
    QAction *actionContact;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonROI;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonBrush;
    QCheckBox *checkBoxClean;
    QSpinBox *spinBoxBrush;
    QToolButton *toolButtonBrushSize;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolButtonFinish;
    QToolButton *toolButtonGrabCut;
    ImageViewer *graphicsView;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBoxLightningMode;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditSetLabel;
    QToolButton *toolButtonSetLabel;
    QTableView *tableViewLabel;
    QMenuBar *menuBar;
    QMenu *menufile;
    QMenu *menulabels;
    QMenu *menuSave_as;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GrabLabelClass)
    {
        if (GrabLabelClass->objectName().isEmpty())
            GrabLabelClass->setObjectName(QStringLiteral("GrabLabelClass"));
        GrabLabelClass->resize(597, 455);
        actionOpenImg = new QAction(GrabLabelClass);
        actionOpenImg->setObjectName(QStringLiteral("actionOpenImg"));
        actionOpenImg->setCheckable(false);
        actionSaveGray = new QAction(GrabLabelClass);
        actionSaveGray->setObjectName(QStringLiteral("actionSaveGray"));
        actionRGB = new QAction(GrabLabelClass);
        actionRGB->setObjectName(QStringLiteral("actionRGB"));
        actionLoadLabel = new QAction(GrabLabelClass);
        actionLoadLabel->setObjectName(QStringLiteral("actionLoadLabel"));
        actionCloseImg = new QAction(GrabLabelClass);
        actionCloseImg->setObjectName(QStringLiteral("actionCloseImg"));
        actionSaveAsGray = new QAction(GrabLabelClass);
        actionSaveAsGray->setObjectName(QStringLiteral("actionSaveAsGray"));
        actionSaveAsRGB = new QAction(GrabLabelClass);
        actionSaveAsRGB->setObjectName(QStringLiteral("actionSaveAsRGB"));
        actionCloseLabel = new QAction(GrabLabelClass);
        actionCloseLabel->setObjectName(QStringLiteral("actionCloseLabel"));
        actionHelp = new QAction(GrabLabelClass);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionContact = new QAction(GrabLabelClass);
        actionContact->setObjectName(QStringLiteral("actionContact"));
        centralWidget = new QWidget(GrabLabelClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButtonROI = new QRadioButton(centralWidget);
        radioButtonROI->setObjectName(QStringLiteral("radioButtonROI"));

        verticalLayout->addWidget(radioButtonROI);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioButtonBrush = new QRadioButton(centralWidget);
        radioButtonBrush->setObjectName(QStringLiteral("radioButtonBrush"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButtonBrush->sizePolicy().hasHeightForWidth());
        radioButtonBrush->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(radioButtonBrush);

        checkBoxClean = new QCheckBox(centralWidget);
        checkBoxClean->setObjectName(QStringLiteral("checkBoxClean"));
        sizePolicy.setHeightForWidth(checkBoxClean->sizePolicy().hasHeightForWidth());
        checkBoxClean->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(checkBoxClean);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(verticalLayout);

        spinBoxBrush = new QSpinBox(centralWidget);
        spinBoxBrush->setObjectName(QStringLiteral("spinBoxBrush"));
        sizePolicy.setHeightForWidth(spinBoxBrush->sizePolicy().hasHeightForWidth());
        spinBoxBrush->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(spinBoxBrush);

        toolButtonBrushSize = new QToolButton(centralWidget);
        toolButtonBrushSize->setObjectName(QStringLiteral("toolButtonBrushSize"));

        horizontalLayout_4->addWidget(toolButtonBrushSize);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        toolButtonFinish = new QToolButton(centralWidget);
        toolButtonFinish->setObjectName(QStringLiteral("toolButtonFinish"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButtonFinish->sizePolicy().hasHeightForWidth());
        toolButtonFinish->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(toolButtonFinish);

        toolButtonGrabCut = new QToolButton(centralWidget);
        toolButtonGrabCut->setObjectName(QStringLiteral("toolButtonGrabCut"));
        sizePolicy1.setHeightForWidth(toolButtonGrabCut->sizePolicy().hasHeightForWidth());
        toolButtonGrabCut->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(toolButtonGrabCut);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_4);

        graphicsView = new ImageViewer(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout_4->addWidget(graphicsView);


        horizontalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        checkBoxLightningMode = new QCheckBox(centralWidget);
        checkBoxLightningMode->setObjectName(QStringLiteral("checkBoxLightningMode"));

        verticalLayout_5->addWidget(checkBoxLightningMode);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEditSetLabel = new QLineEdit(centralWidget);
        lineEditSetLabel->setObjectName(QStringLiteral("lineEditSetLabel"));
        sizePolicy.setHeightForWidth(lineEditSetLabel->sizePolicy().hasHeightForWidth());
        lineEditSetLabel->setSizePolicy(sizePolicy);
        lineEditSetLabel->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(lineEditSetLabel);

        toolButtonSetLabel = new QToolButton(centralWidget);
        toolButtonSetLabel->setObjectName(QStringLiteral("toolButtonSetLabel"));
        sizePolicy.setHeightForWidth(toolButtonSetLabel->sizePolicy().hasHeightForWidth());
        toolButtonSetLabel->setSizePolicy(sizePolicy);
        toolButtonSetLabel->setMaximumSize(QSize(100, 50));

        horizontalLayout_2->addWidget(toolButtonSetLabel);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_5->addLayout(verticalLayout_3);

        tableViewLabel = new QTableView(centralWidget);
        tableViewLabel->setObjectName(QStringLiteral("tableViewLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableViewLabel->sizePolicy().hasHeightForWidth());
        tableViewLabel->setSizePolicy(sizePolicy2);
        tableViewLabel->setMaximumSize(QSize(180, 16777215));

        verticalLayout_5->addWidget(tableViewLabel);


        horizontalLayout_5->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_5);

        GrabLabelClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GrabLabelClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 597, 23));
        menufile = new QMenu(menuBar);
        menufile->setObjectName(QStringLiteral("menufile"));
        menulabels = new QMenu(menuBar);
        menulabels->setObjectName(QStringLiteral("menulabels"));
        menuSave_as = new QMenu(menulabels);
        menuSave_as->setObjectName(QStringLiteral("menuSave_as"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        GrabLabelClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GrabLabelClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GrabLabelClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GrabLabelClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GrabLabelClass->setStatusBar(statusBar);

        menuBar->addAction(menufile->menuAction());
        menuBar->addAction(menulabels->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menufile->addAction(actionOpenImg);
        menufile->addAction(actionCloseImg);
        menulabels->addAction(actionLoadLabel);
        menulabels->addAction(menuSave_as->menuAction());
        menulabels->addAction(actionCloseLabel);
        menuSave_as->addAction(actionSaveAsGray);
        menuSave_as->addAction(actionSaveAsRGB);
        menuAbout->addAction(actionHelp);
        menuAbout->addAction(actionContact);

        retranslateUi(GrabLabelClass);

        QMetaObject::connectSlotsByName(GrabLabelClass);
    } // setupUi

    void retranslateUi(QMainWindow *GrabLabelClass)
    {
        GrabLabelClass->setWindowTitle(QApplication::translate("GrabLabelClass", "GrabLabel", Q_NULLPTR));
        actionOpenImg->setText(QApplication::translate("GrabLabelClass", "Open...", Q_NULLPTR));
        actionSaveGray->setText(QApplication::translate("GrabLabelClass", "Grey", Q_NULLPTR));
        actionRGB->setText(QApplication::translate("GrabLabelClass", "RGB", Q_NULLPTR));
        actionLoadLabel->setText(QApplication::translate("GrabLabelClass", "Load txt...", Q_NULLPTR));
        actionCloseImg->setText(QApplication::translate("GrabLabelClass", "Close", Q_NULLPTR));
        actionSaveAsGray->setText(QApplication::translate("GrabLabelClass", "Gray", Q_NULLPTR));
        actionSaveAsRGB->setText(QApplication::translate("GrabLabelClass", "RGB", Q_NULLPTR));
        actionCloseLabel->setText(QApplication::translate("GrabLabelClass", "Close txt", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("GrabLabelClass", "Help", Q_NULLPTR));
        actionContact->setText(QApplication::translate("GrabLabelClass", "Contact", Q_NULLPTR));
        radioButtonROI->setText(QApplication::translate("GrabLabelClass", "ROI", Q_NULLPTR));
        radioButtonBrush->setText(QApplication::translate("GrabLabelClass", "Brush", Q_NULLPTR));
        checkBoxClean->setText(QApplication::translate("GrabLabelClass", "Clean", Q_NULLPTR));
        toolButtonBrushSize->setText(QApplication::translate("GrabLabelClass", "Brush Size", Q_NULLPTR));
        toolButtonFinish->setText(QApplication::translate("GrabLabelClass", "Finish", Q_NULLPTR));
        toolButtonGrabCut->setText(QApplication::translate("GrabLabelClass", "GrabCut", Q_NULLPTR));
        checkBoxLightningMode->setText(QApplication::translate("GrabLabelClass", "Lightning Mode", Q_NULLPTR));
        toolButtonSetLabel->setText(QApplication::translate("GrabLabelClass", "Set Label", Q_NULLPTR));
        menufile->setTitle(QApplication::translate("GrabLabelClass", "Image", Q_NULLPTR));
        menulabels->setTitle(QApplication::translate("GrabLabelClass", "Label", Q_NULLPTR));
        menuSave_as->setTitle(QApplication::translate("GrabLabelClass", "Save as", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("GrabLabelClass", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GrabLabelClass: public Ui_GrabLabelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRABLABEL_H

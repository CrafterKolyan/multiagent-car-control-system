/********************************************************************************
** Form generated from reading UI file 'maska.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASKA_H
#define UI_MASKA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Maska
{
public:
    QAction *actionSettings;
    QAction *actionSettings_2;
    QAction *action123;
    QAction *action123_2;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *addCar;
    QPushButton *deleteCar;
    QGraphicsView *mapViewConst;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Maska)
    {
        if (Maska->objectName().isEmpty())
            Maska->setObjectName(QStringLiteral("Maska"));
        Maska->resize(665, 402);
        actionSettings = new QAction(Maska);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionSettings_2 = new QAction(Maska);
        actionSettings_2->setObjectName(QStringLiteral("actionSettings_2"));
        action123 = new QAction(Maska);
        action123->setObjectName(QStringLiteral("action123"));
        action123_2 = new QAction(Maska);
        action123_2->setObjectName(QStringLiteral("action123_2"));
        centralWidget = new QWidget(Maska);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        addCar = new QPushButton(centralWidget);
        addCar->setObjectName(QStringLiteral("addCar"));
        addCar->setCheckable(false);

        gridLayout->addWidget(addCar, 0, 0, 1, 1);

        deleteCar = new QPushButton(centralWidget);
        deleteCar->setObjectName(QStringLiteral("deleteCar"));

        gridLayout->addWidget(deleteCar, 0, 1, 1, 1);

        mapViewConst = new QGraphicsView(centralWidget);
        mapViewConst->setObjectName(QStringLiteral("mapViewConst"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapViewConst->sizePolicy().hasHeightForWidth());
        mapViewConst->setSizePolicy(sizePolicy);

        gridLayout->addWidget(mapViewConst, 0, 2, 3, 1);

        Maska->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Maska);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Maska->setStatusBar(statusBar);

        retranslateUi(Maska);

        QMetaObject::connectSlotsByName(Maska);
    } // setupUi

    void retranslateUi(QMainWindow *Maska)
    {
        Maska->setWindowTitle(QApplication::translate("Maska", "Maska", 0));
        actionSettings->setText(QApplication::translate("Maska", "Settings", 0));
        actionSettings_2->setText(QApplication::translate("Maska", "Settings", 0));
        action123->setText(QApplication::translate("Maska", "123", 0));
        action123_2->setText(QApplication::translate("Maska", "123", 0));
        addCar->setText(QApplication::translate("Maska", "Car +", 0));
        deleteCar->setText(QApplication::translate("Maska", "Car -", 0));
    } // retranslateUi

};

namespace Ui {
    class Maska: public Ui_Maska {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASKA_H

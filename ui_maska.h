/********************************************************************************
** Form generated from reading UI file 'maska.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Maska
{
public:
    QAction *actionRandomALL;
    QAction *actionRandom_unset_destinations;
    QAction *actionSticky_Random;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *mapViewConst;
    QPushButton *decSpeed;
    QPushButton *addSpeed;
    QPushButton *nextTurn;
    QPushButton *reset;
    QPushButton *autoNextTurn;
    QPushButton *addCar;
    QPushButton *deleteCar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuRandom;

    void setupUi(QMainWindow *Maska)
    {
        if (Maska->objectName().isEmpty())
            Maska->setObjectName(QStringLiteral("Maska"));
        Maska->setWindowModality(Qt::NonModal);
        Maska->resize(665, 402);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Maska->sizePolicy().hasHeightForWidth());
        Maska->setSizePolicy(sizePolicy);
        Maska->setLayoutDirection(Qt::LeftToRight);
        Maska->setDocumentMode(false);
        actionRandomALL = new QAction(Maska);
        actionRandomALL->setObjectName(QStringLiteral("actionRandomALL"));
        actionRandom_unset_destinations = new QAction(Maska);
        actionRandom_unset_destinations->setObjectName(QStringLiteral("actionRandom_unset_destinations"));
        actionSticky_Random = new QAction(Maska);
        actionSticky_Random->setObjectName(QStringLiteral("actionSticky_Random"));
        actionSticky_Random->setCheckable(true);
        centralWidget = new QWidget(Maska);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mapViewConst = new QGraphicsView(centralWidget);
        mapViewConst->setObjectName(QStringLiteral("mapViewConst"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mapViewConst->sizePolicy().hasHeightForWidth());
        mapViewConst->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(mapViewConst, 0, 3, 5, 1);

        decSpeed = new QPushButton(centralWidget);
        decSpeed->setObjectName(QStringLiteral("decSpeed"));

        gridLayout->addWidget(decSpeed, 1, 1, 1, 1);

        addSpeed = new QPushButton(centralWidget);
        addSpeed->setObjectName(QStringLiteral("addSpeed"));

        gridLayout->addWidget(addSpeed, 1, 0, 1, 1);

        nextTurn = new QPushButton(centralWidget);
        nextTurn->setObjectName(QStringLiteral("nextTurn"));

        gridLayout->addWidget(nextTurn, 2, 0, 1, 1);

        reset = new QPushButton(centralWidget);
        reset->setObjectName(QStringLiteral("reset"));

        gridLayout->addWidget(reset, 2, 1, 1, 1);

        autoNextTurn = new QPushButton(centralWidget);
        autoNextTurn->setObjectName(QStringLiteral("autoNextTurn"));
        autoNextTurn->setCheckable(true);

        gridLayout->addWidget(autoNextTurn, 0, 0, 1, 2);

        addCar = new QPushButton(centralWidget);
        addCar->setObjectName(QStringLiteral("addCar"));
        addCar->setCheckable(false);

        gridLayout->addWidget(addCar, 3, 0, 1, 1);

        deleteCar = new QPushButton(centralWidget);
        deleteCar->setObjectName(QStringLiteral("deleteCar"));
        deleteCar->setMinimumSize(QSize(75, 23));

        gridLayout->addWidget(deleteCar, 3, 1, 1, 1);

        Maska->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Maska);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Maska->setStatusBar(statusBar);
        menuBar = new QMenuBar(Maska);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 665, 21));
        menuRandom = new QMenu(menuBar);
        menuRandom->setObjectName(QStringLiteral("menuRandom"));
        Maska->setMenuBar(menuBar);

        menuBar->addAction(menuRandom->menuAction());
        menuRandom->addAction(actionRandomALL);
        menuRandom->addAction(actionRandom_unset_destinations);
        menuRandom->addAction(actionSticky_Random);

        retranslateUi(Maska);

        QMetaObject::connectSlotsByName(Maska);
    } // setupUi

    void retranslateUi(QMainWindow *Maska)
    {
        Maska->setWindowTitle(QApplication::translate("Maska", "Maska", 0));
        actionRandomALL->setText(QApplication::translate("Maska", "Random all destinations", 0));
        actionRandom_unset_destinations->setText(QApplication::translate("Maska", "Random unset destinations", 0));
        actionSticky_Random->setText(QApplication::translate("Maska", "Auto Random", 0));
        decSpeed->setText(QApplication::translate("Maska", "Speed -", 0));
        addSpeed->setText(QApplication::translate("Maska", "Speed +", 0));
        nextTurn->setText(QApplication::translate("Maska", "Next Turn", 0));
        reset->setText(QApplication::translate("Maska", "Reset", 0));
        autoNextTurn->setText(QApplication::translate("Maska", "Auto Next Turn", 0));
        addCar->setText(QApplication::translate("Maska", "Car +", 0));
        deleteCar->setText(QApplication::translate("Maska", "Car -", 0));
        menuRandom->setTitle(QApplication::translate("Maska", "Random", 0));
    } // retranslateUi

};

namespace Ui {
    class Maska: public Ui_Maska {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASKA_H

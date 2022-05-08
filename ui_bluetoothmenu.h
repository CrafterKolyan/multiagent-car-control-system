/********************************************************************************
** Form generated from reading UI file 'bluetoothmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTHMENU_H
#define UI_BLUETOOTHMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BluetoothMenu
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *labelStatus;
    QLabel *labelBluetooth;
    QCheckBox *checkBoxStatus;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BluetoothMenu)
    {
        if (BluetoothMenu->objectName().isEmpty())
            BluetoothMenu->setObjectName(QStringLiteral("BluetoothMenu"));
        BluetoothMenu->resize(465, 339);
        centralwidget = new QWidget(BluetoothMenu);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 421, 271));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelStatus = new QLabel(gridLayoutWidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelStatus->setFont(font);

        gridLayout->addWidget(labelStatus, 0, 1, 1, 1);

        labelBluetooth = new QLabel(gridLayoutWidget);
        labelBluetooth->setObjectName(QStringLiteral("labelBluetooth"));

        gridLayout->addWidget(labelBluetooth, 0, 0, 1, 1);

        checkBoxStatus = new QCheckBox(gridLayoutWidget);
        checkBoxStatus->setObjectName(QStringLiteral("checkBoxStatus"));

        gridLayout->addWidget(checkBoxStatus, 0, 2, 1, 1);

        BluetoothMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BluetoothMenu);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 465, 27));
        BluetoothMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(BluetoothMenu);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        BluetoothMenu->setStatusBar(statusbar);

        retranslateUi(BluetoothMenu);

        QMetaObject::connectSlotsByName(BluetoothMenu);
    } // setupUi

    void retranslateUi(QMainWindow *BluetoothMenu)
    {
        BluetoothMenu->setWindowTitle(QApplication::translate("BluetoothMenu", "Bluetooth Info", 0));
        labelStatus->setText(QApplication::translate("BluetoothMenu", "NO INFO", 0));
        labelBluetooth->setText(QApplication::translate("BluetoothMenu", "Bluetooth Status: ", 0));
        checkBoxStatus->setText(QApplication::translate("BluetoothMenu", "Bluetooth Power", 0));
    } // retranslateUi

};

namespace Ui {
    class BluetoothMenu: public Ui_BluetoothMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTHMENU_H

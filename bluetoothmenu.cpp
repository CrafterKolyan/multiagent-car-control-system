#include "bluetoothmenu.h"
#include "ui_bluetoothmenu.h"

#include <QDebug>

BluetoothMenu::BluetoothMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BluetoothMenu)
{
    ui->setupUi(this);
    localDevice = new QBluetoothLocalDevice;
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent;

    connect(localDevice, SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
            this, SLOT(hostModeStateChanged(QBluetoothLocalDevice::HostMode)));

    if(localDevice->hostMode() != QBluetoothLocalDevice::HostPoweredOff){
        ui->labelStatus->setText("ON");
        ui->checkBoxStatus->setChecked(1);
    }else{
        ui->labelStatus->setText("OFF");
    }
}

BluetoothMenu::~BluetoothMenu()
{
    delete ui;
    delete localDevice;
    delete discoveryAgent;
}

void BluetoothMenu::on_checkBoxStatus_toggled(bool checked)
{
    qDebug() << checked;
    if(checked){
        localDevice->powerOn();
    }else{
        localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    }
}

void BluetoothMenu::hostModeStateChanged(QBluetoothLocalDevice::HostMode hostmode){
    if(hostmode == QBluetoothLocalDevice::HostPoweredOff){
        ui->labelStatus->setText("OFF");
        ui->checkBoxStatus->setChecked(0);
    }else{
        ui->labelStatus->setText("ON");
        ui->checkBoxStatus->setChecked(1);
    }
}

#ifndef BLUETOOTHMENU_H
#define BLUETOOTHMENU_H

#include <QMainWindow>
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothAddress>
#include <QBluetoothDeviceDiscoveryAgent>

namespace Ui {
class BluetoothMenu;
}

class BluetoothMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit BluetoothMenu(QWidget *parent = 0);
    ~BluetoothMenu();

private slots:
    void on_checkBoxStatus_toggled(bool checked);
    void hostModeStateChanged(QBluetoothLocalDevice::HostMode);

private:
    Ui::BluetoothMenu *ui;
    QBluetoothLocalDevice *localDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
};

#endif // BLUETOOTHMENU_H

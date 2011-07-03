#ifndef DEVICESELECTVIEW_HPP
#define DEVICESELECTVIEW_HPP

#include <iostream>
#include <string>
#include <QDialog>
#include <QString>

#include "libvm/CameraVM.hpp"

namespace Ui {
    class DeviceSelectView;
}

class DeviceSelectView : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceSelectView(QWidget *parent = 0);
    ~DeviceSelectView();

public slots:

    void accept();
    void reject();

private:
    void loadDevices();

    Ui::DeviceSelectView *ui;

    vm::CameraVM* _cameraVM;
    std::set<int> _devices;
    QString _selectedDevice;
};

#endif // DEVICESELECTVIEW_HPP

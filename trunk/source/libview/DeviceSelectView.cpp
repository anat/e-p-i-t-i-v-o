#include "DeviceSelectView.hpp"
#include "ui_DeviceSelectView.h"

DeviceSelectView::DeviceSelectView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceSelectView)
{
    ui->setupUi(this);

    _cameraVM = vm::CameraVM::GetInstance();
    _selectedDevice = "0";

    connect(ui->selCamOkBtn, SIGNAL(clicked()),
            this, SLOT(accept()));
    connect(ui->selCamCancelBtn, SIGNAL(clicked()),
            this, SLOT(reject()));

    this->loadDevices();
}

DeviceSelectView::~DeviceSelectView()
{
    delete ui;
}

void DeviceSelectView::loadDevices()
{
    _devices = _cameraVM->getCamDevices();
    std::set<int>::const_iterator it;

    ui->devicesSelComboBox->addItem("0");
    for ( it=_devices.begin() ; it != _devices.end(); it++ )
    {
      int val = *it;
      std::string s;
      std::stringstream out;
      out << val;
      s = out.str();
      QString qstr(s.c_str());
      ui->devicesSelComboBox->addItem(qstr);
    }

}

void DeviceSelectView::accept()
{
    _selectedDevice = ui->devicesSelComboBox->currentText();
    _cameraVM->_cameras = atoi((_selectedDevice.toStdString()).c_str());
    this->close();
    QDialog::accept();
}

void DeviceSelectView::reject()
{
    QDialog::reject();
}



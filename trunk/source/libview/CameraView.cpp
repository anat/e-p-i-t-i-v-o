#include "CameraView.hpp"
#include "ui_CameraView.h"
#include <iostream>

#include <sstream>

CameraView::CameraView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraView)
{
    ui->setupUi(this);

  ui->startCamRecBtn->setVisible(true);
  ui->pauseCamRecBtn->setVisible(false);

  _vm = vm::CameraVM::GetInstance();
  _vm->mapSurface(ui->imgBoxLabel);

  this->selectInputDevice();
  this->setCameraConnects(true);
}

CameraView::~CameraView()
{
    _vm->DelInstance();
    delete ui;
}

void CameraView::setCameraConnects(bool state)
{
  if (state)
  {
    connect(ui->startCamRecBtn, SIGNAL(clicked()), 
      this, SLOT(recordCam()));

    connect(ui->stopCamRectBtn, SIGNAL(clicked()), 
      this, SLOT(stopRecCam()));

    connect(ui->pauseCamRecBtn, SIGNAL(clicked()), 
      this, SLOT(pauseRecCam()));
  }
  else
  {
    // disconnects
  }
}
void CameraView::StartCam()
{
  _vm->StartCam();
}

void CameraView::StopCam()
{
  _vm->StopCam();
}

void CameraView::PauseCam()
{
  _vm->PauseCam();
}

void CameraView::setRecordingState()
{
    ui->startCamRecBtn->setVisible(false);
    ui->pauseCamRecBtn->setVisible(true);
}

void CameraView::setPausedRecordingState()
{
    ui->startCamRecBtn->setVisible(true);
    ui->pauseCamRecBtn->setVisible(false);
}

void CameraView::setStoppedRecordingState()
{
    ui->startCamRecBtn->setVisible(true);
    ui->pauseCamRecBtn->setVisible(false);
}

void CameraView::recordCam()
{
  this->setRecordingState();
  _vm->StartRecordCam();
}

void CameraView::stopRecCam()
{
  this->setStoppedRecordingState();
  _vm->StopRecCam();
}

void CameraView::pauseRecCam()
{
  this->setPausedRecordingState();
  _vm->PauseRecCam();
}
void CameraView::selectInputDevice()
{
  QDialog dialog;

  QPushButton buttonAccept("OK");

  QComboBox combo;

  std::set<int> const & cams = _vm->getCamDevices();
  std::set<int>::const_iterator it;

    combo.addItem("0");
  for ( it=cams.begin() ; it != cams.end(); it++ )
  {
    int val = *it;
    std::string s;
    std::stringstream out;
    out << val;
    s = out.str();
    QString qstr(s.c_str());
    combo.addItem(qstr);
  }
  _selected = combo.currentText();
  connect(&buttonAccept, SIGNAL(clicked()), this, SLOT((PopupOk())));
  connect(&buttonAccept, SIGNAL(clicked()), &dialog, SLOT((done())));

  QHBoxLayout layout;
  layout.addWidget(&buttonAccept);
  layout.addWidget(&combo);

  dialog.setLayout(&layout);
  dialog.exec();

}

void CameraView::PopupOk()
{
  _vm->_cameras = atoi((_selected.toStdString()).c_str());
}
void CameraView::accept()
{
}

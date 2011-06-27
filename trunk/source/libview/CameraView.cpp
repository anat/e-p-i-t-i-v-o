#include "CameraView.hpp"
#include "ui_CameraView.h"
#include <iostream>

CameraView::CameraView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraView)
{
    ui->setupUi(this);

  ui->startCamRecBtn->setVisible(true);
  ui->pauseCamRecBtn->setVisible(false);

  _vm = vm::CameraVM::GetInstance();
  _vm->mapSurface(ui->imgBoxLabel);

  this->setCameraConnects(true);
}

CameraView::~CameraView()
{
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

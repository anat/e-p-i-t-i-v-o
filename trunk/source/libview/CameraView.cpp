#include "CameraView.hpp"
#include "ui_CameraView.h"

CameraView::CameraView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraView)
{
    ui->setupUi(this);

  ui->startCamBtn->setVisible(true);
  ui->pauseCamBtn->setVisible(false);

  _vm = vm::CameraVM::GetInstance();

  this->setQtConnects();
}

CameraView::~CameraView()
{
    delete ui;
}

void CameraView::setQtConnects()
{
  connect(ui->startCamBtn, SIGNAL(clicked()), this, SLOT(startCam()));
  //connect(ui->pauseCamBtn, SIGNAL(clicked()), this, SLOT(pauseCam()));
  connect(ui->stopCamBtn, SIGNAL(clicked()), this, SLOT(stopCam()));
}

bool CameraView::OpenDevice()
{
  bool ret = true;

  _vm->OpenDevice(ui->imgBoxLabel);
  this->startCam();
  return ret;
}

void CameraView::startCam()
{
  ui->startCamBtn->setVisible(false);
  ui->pauseCamBtn->setVisible(true);
  _vm->StartCam();
}

void CameraView::stopCam()
{
  ui->startCamBtn->setVisible(true);
  ui->pauseCamBtn->setVisible(false);
  _vm->StopCam();
}

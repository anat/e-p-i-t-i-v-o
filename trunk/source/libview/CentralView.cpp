#include "CentralView.hpp"
#include "ui_CentralView.h"

CentralView::CentralView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CentralView),
    _cameraView(0)
{
  ui->setupUi(this);
  _vm = vm::CentralVM::GetInstance();

  ui->pauseBtn->setVisible(false);
}

CentralView::~CentralView()
{
  delete _cameraView;
  delete ui;
}

void CentralView::OpenFile()
{
  QString homePath = QDir::homePath();
  QString fileName = QFileDialog::getOpenFileName(
      this,
      tr("Open a media ..."),
      homePath,
      tr("Images (*.png *.xpm *.jpg);;Videos (*.txt)")
      );
  //if (_vm->OpenFile(fileName))
  //{
  //}
}

void CentralView::OpenCameraDevice()
{
  this->createCameraView();
  ui->centralContainer->addWidget(_cameraView);
  this->setCameraViewQtConnects(true);
}

CameraView* CentralView::createCameraView()
{
  if (_cameraView == 0)
    _cameraView = new CameraView;
  return _cameraView;
}

void CentralView::clearCameraView()
{
  if (_cameraView != 0)
  {
    delete _cameraView;
    _cameraView = 0;
  }
}

void CentralView::setCameraViewQtConnects(bool state)
{
  if (state)
  {
    connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(setPlayingMediaState()));
    connect(ui->playBtn, SIGNAL(clicked()), _cameraView, SLOT(StartCam()));

    connect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(setStoppedMediaState()));
    connect(ui->stopBtn, SIGNAL(clicked()), _cameraView, SLOT(StopCam()));

    connect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(setPausedMediaState()));
    connect(ui->pauseBtn, SIGNAL(clicked()), _cameraView, SLOT(PauseCam()));
  }
  else
  {
    // disconnects
  }
}

void CentralView::setPlayingMediaState()
{
    ui->playBtn->setVisible(false);
    ui->pauseBtn->setVisible(true);
}

void CentralView::setPausedMediaState()
{
    ui->playBtn->setVisible(true);
    ui->pauseBtn->setVisible(false);
}

void CentralView::setStoppedMediaState()
{
    ui->playBtn->setVisible(true);
    ui->pauseBtn->setVisible(false);
}

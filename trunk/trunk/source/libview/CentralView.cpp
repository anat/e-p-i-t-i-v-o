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
  delete _playerView;
  delete ui;
}

void CentralView::OpenFile()
{
  QString homePath = QDir::homePath();
  QString fileName = QFileDialog::getOpenFileName(
      this,
      tr("Open a media ..."),
      homePath,
      tr("Epitivo file (*.epitivo)")
      );
  if (fileName.size() > 0)
  {
    if (ui->centralContainer->count() > 0)
    {
      this->clearPlayerView();
      this->clearCameraView();
    }
    this->createPlayerView();
    _playerView->setFilepath(fileName);
    ui->centralContainer->addWidget(_playerView);
  }
}

void CentralView::OpenCameraDevice()
{
  if (ui->centralContainer->count() > 0)
  {
    this->clearPlayerView();
    this->clearCameraView();
  }
  this->createCameraView();
  ui->centralContainer->addWidget(_cameraView);
}

CameraView* CentralView::createCameraView()
{
  if (_cameraView == 0)
    _cameraView = new CameraView;
  this->setCameraViewQtConnects(true);
  return _cameraView;
}

void CentralView::clearCameraView()
{
  if (_cameraView != 0)
  {
    this->setCameraViewQtConnects(false);
    ui->centralContainer->removeWidget(_cameraView);
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
    disconnect(ui->playBtn, SIGNAL(clicked()), this, SLOT(setPlayingMediaState()));
    disconnect(ui->playBtn, SIGNAL(clicked()), _cameraView, SLOT(StartCam()));

    disconnect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(setStoppedMediaState()));
    disconnect(ui->stopBtn, SIGNAL(clicked()), _cameraView, SLOT(StopCam()));

    disconnect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(setPausedMediaState()));
    disconnect(ui->pauseBtn, SIGNAL(clicked()), _cameraView, SLOT(PauseCam()));
  }
}

PlayerView* CentralView::createPlayerView()
{
  if (_playerView == 0)
    _playerView = new PlayerView;
  this->setPlayerViewQtConnects(true);
  return _playerView;
}

void CentralView::clearPlayerView()
{
  if (_playerView != 0)
  {
  this->setPlayerViewQtConnects(false);
    ui->centralContainer->removeWidget(_playerView);
    delete _playerView;
    _playerView = 0;
  }
}
void CentralView::setPlayerViewQtConnects(bool state)
{
  if (state)
  {
    connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(setPlayingMediaState()));
    connect(ui->playBtn, SIGNAL(clicked()), _playerView, SLOT(Play()));

    connect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(setStoppedMediaState()));
    connect(ui->stopBtn, SIGNAL(clicked()), _playerView, SLOT(Stop()));

    connect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(setPausedMediaState()));
    connect(ui->pauseBtn, SIGNAL(clicked()), _playerView, SLOT(Pause()));
  }
  else
  {
    // disconnects
    disconnect(ui->playBtn, SIGNAL(clicked()), this, SLOT(setPlayingMediaState()));
    disconnect(ui->playBtn, SIGNAL(clicked()), _playerView, SLOT(Play()));

    disconnect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(setStoppedMediaState()));
    disconnect(ui->stopBtn, SIGNAL(clicked()), _playerView, SLOT(Stop()));

    disconnect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(setPausedMediaState()));
    disconnect(ui->pauseBtn, SIGNAL(clicked()), _playerView, SLOT(Pause()));
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

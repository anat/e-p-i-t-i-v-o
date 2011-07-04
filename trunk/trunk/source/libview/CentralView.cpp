#include "CentralView.hpp"
#include "ui_CentralView.h"
#include "playlistwidget.hpp"
CentralView *CentralView::_instance = 0;

CentralView::CentralView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CentralView),
    _cameraView(0)
{
  ui->setupUi(this);
  _vm = vm::CentralVM::GetInstance();

  _isPaused = false;
}

CentralView* CentralView::GetInstance()
{
    if (!_instance)
        _instance = new CentralView;
    return _instance;
}

void CentralView::DelInstance()
{
    if (_instance)
        delete _instance;
}

CentralView::~CentralView()
{
  this->clearCameraView();
  this->clearPlayerView();
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
  this->LoadVideo(fileName.toStdString());
}

void CentralView::LoadVideo(std::string path)
{
    std::cout << "Loading " << path << std::endl;
    if (path.size() > 0)
    {
      if (ui->centralContainer->count() > 0)
      {
        this->clearPlayerView();
        this->clearCameraView();
      }
      this->createPlayerView();
      _playerView->setFilepath(path.c_str());
      ui->centralContainer->addWidget(_playerView);
    }
}



void CentralView::setShit()
         { ui->centralContainer->addWidget(_playerView);}
void CentralView::OpenCameraDevice()
{
  if (ui->centralContainer->count() > 0)
  {
    this->clearPlayerView();
    this->clearCameraView();

  }

  this->createCameraView();

  ui->centralContainer->addWidget(_cameraView);
  //this->setPlayingMediaState();

  _cameraView->StartCam();
    QApplication::processEvents();
}

CameraView* CentralView::createCameraView()
{
     //vm::CameraVM::DelInstance();
    // vm::CameraVM::GetInstance();
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
    //connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(setPlayingMediaState()));
    connect(ui->playBtn, SIGNAL(clicked()), _cameraView, SLOT(StartCam()));

    //connect(ui->recBtn, SIGNAL(clicked()), this, SLOT(setPlayingMediaState()));
    connect(ui->recBtn, SIGNAL(clicked()), _cameraView, SLOT(recordCam()));

    //connect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(setStoppedMediaState()));
    connect(ui->stopBtn, SIGNAL(clicked()), _cameraView, SLOT(stopRecCam()));

    //connect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(setPausedMediaState()));
    connect(ui->pauseBtn, SIGNAL(clicked()), _cameraView, SLOT(pauseRecCam()));
  }
  else
  {
    // disconnects
    //disconnect(ui->playBtn, SIGNAL(clicked()), this, SLOT(setPlayingMediaState()));
    disconnect(ui->playBtn, SIGNAL(clicked()), _cameraView, SLOT(StartCam()));

    disconnect(ui->recBtn, SIGNAL(clicked()), _cameraView, SLOT(recordCam()));

    //disconnect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(setStoppedMediaState()));
    disconnect(ui->stopBtn, SIGNAL(clicked()), _cameraView, SLOT(stopRecCam()));

    //disconnect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(setPausedMediaState()));
    disconnect(ui->pauseBtn, SIGNAL(clicked()), _cameraView, SLOT(pauseRecCam()));
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
    _isPaused = false;
}

void CentralView::setPausedMediaState()
{
    ui->playBtn->setVisible(true);
    ui->pauseBtn->setVisible(false);
    _isPaused = true;
}

void CentralView::setStoppedMediaState()
{
    ui->playBtn->setVisible(true);
    ui->pauseBtn->setVisible(false);
    _isPaused = false;
}

void CentralView::OpenPlayList()
{
    PlayListWidget::GetInstance()->show();
}


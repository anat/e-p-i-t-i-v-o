#include "MainWindow.hpp"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _centralView(NULL),
    _cameraView(NULL)
{
  ui->setupUi(this);
  _vm = vm::MainWindowVM::GetInstance();
  //this->setCentralWidget(_centralView);

  this->setQtConnects();
}

MainWindow::~MainWindow()
{
  delete _centralView;
  delete ui;
}

void MainWindow::openFile()
{
  QString homePath = QDir::homePath();
  QString fileName = QFileDialog::getOpenFileName(
      this,
      tr("Open a media ..."),
      homePath,
      tr("Images (*.png *.xpm *.jpg);;Videos (*.txt)")
      );
  if (_vm->openFile(fileName))
  {
    //this->setCentralWidget(this->createCameraView);
  }
}

void MainWindow::openDevice()
{
  this->setCentralWidget(this->createCameraView());
  this->updateGeometry();
  _cameraView->OpenDevice();
}
void MainWindow::setQtConnects()
{
  connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(openFile()));
  connect(ui->actionOpen_device, SIGNAL(triggered()), this, SLOT(openDevice()));
}

CameraView* MainWindow::createCameraView()
{
  if (_cameraView == 0)
    _cameraView = new CameraView;
  return _cameraView;
}

CentralView* MainWindow::createCentralView()
{
  if (_centralView == 0)
    _centralView = new CentralView;
  return _centralView;
}


#include "MainWindow.hpp"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _centralView(new CentralView)
{
  ui->setupUi(this);
  _dataContext = vm::MainWindowVM::GetInstance();
  this->setCentralWidget(_centralView);

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


  //if (!fileName.isEmpty())
  //openFile(fileName);
}

void MainWindow::setQtConnects()
{

  connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(openFile()));
}

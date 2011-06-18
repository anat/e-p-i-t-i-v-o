#include "MainWindow.hpp"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _centralView(new CentralView)
{
  ui->setupUi(this);
  this->setCentralWidget(_centralView);
}

MainWindow::~MainWindow()
{
    delete _centralView;
    delete ui;
}

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>

#include "libvm/MainWindowVM.hpp"
#include "CentralView.hpp"
#include "CameraView.hpp"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void openFile();
  void openDevice();

private:
  Ui::MainWindow* ui;

  vm::MainWindowVM* _vm;

  CentralView*    _centralView;
  CameraView*    _cameraView;

  void setQtConnects();

  CameraView* createCameraView();
  CentralView* createCentralView();
};

#endif // MAINWINDOW_HPP

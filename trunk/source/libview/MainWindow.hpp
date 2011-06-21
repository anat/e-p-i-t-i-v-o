#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include "CentralView.hpp"
#include "BottomBar.hpp"
#include "libvm/MainWindowVM.hpp"

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

private:
  Ui::MainWindow* ui;

  vm::MainWindowVM* _dataContext;

  CentralView*    _centralView;
  BottomBar*      _bottomBar;

  void setQtConnects();
};

#endif // MAINWINDOW_HPP

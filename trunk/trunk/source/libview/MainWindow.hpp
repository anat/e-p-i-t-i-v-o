#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "libvm/MainWindowVM.hpp"
#include "CentralView.hpp"

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
    void appExit();

  private:
    Ui::MainWindow* ui;

    vm::MainWindowVM* _vm;

    CentralView*  _centralView;

    void setMainWindowConnects();
    void setMenuConnects();

    CentralView* createCentralView();
    void clearCentralView();

};

#endif // MAINWINDOW_HPP

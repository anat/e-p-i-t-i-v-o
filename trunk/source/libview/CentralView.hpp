#ifndef CENTRALVIEW_HPP
#define CENTRALVIEW_HPP

#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QString>

#include <iostream>

#include "CentralView.hpp"
#include "libvm/CentralVM.hpp"
#include "CameraView.hpp"

namespace Ui {
  class CentralView;
}

class CentralView : public QWidget
{
  Q_OBJECT

  public:
    explicit CentralView(QWidget *parent = 0);
    ~CentralView();

    public slots:
      void OpenFile();
    void OpenCameraDevice();

  private slots:

    void setPlayingMediaState();
    void setPausedMediaState();
    void setStoppedMediaState();

  private:
    Ui::CentralView *ui;

    vm::CentralVM* _vm;

    CameraView*   _cameraView;

    void setCameraViewQtConnects(bool state);

    CameraView* createCameraView();
    void clearCameraView();

};

#endif // CENTRALVIEW_HPP

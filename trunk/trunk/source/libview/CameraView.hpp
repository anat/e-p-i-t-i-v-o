#ifndef CAMERAVIEW_HPP
#define CAMERAVIEW_HPP

#include <QWidget>
#include <QImage>

#include "libvm/CameraVM.hpp"

namespace Ui {
    class CameraView;
}

class CameraView : public QWidget
{
    Q_OBJECT

public:
    explicit CameraView(QWidget *parent = 0);
    ~CameraView();

    bool OpenDevice();

private slots:
void startCam();
void stopCam();

private:
    Ui::CameraView *ui;
  vm::CameraVM* _vm;

  void setQtConnects();
};

#endif // CAMERAVIEW_HPP

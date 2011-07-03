#ifndef CAMERAVIEW_HPP
#define CAMERAVIEW_HPP

#include <set>
#include <QWidget>
#include <QImage>
#include <QDialog>
#include <QComboBox>
#include <stdlib.h>
#include <QPushButton>

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

    public slots:
    void StartCam();
    void StopCam();

    void recordCam();
    void stopRecCam();
    void pauseRecCam();

  private:
    Ui::CameraView *ui;
    vm::CameraVM* _vm;


    QString _selected;

    void selectInputDevice();
};

#endif // CAMERAVIEW_HPP

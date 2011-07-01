#ifndef CAMERAVIEW_HPP
#define CAMERAVIEW_HPP

#include <set>
#include <QWidget>
#include <QImage>
#include <QDialog>
#include <QComboBox>
#include <stdlib.h>
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
    void PauseCam();

    void PopupOk();

    private slots:
    void recordCam();
    void stopRecCam();
    void pauseRecCam();
void accept();

  private:
    Ui::CameraView *ui;
    vm::CameraVM* _vm;

    QString _selected;

    void setCameraConnects(bool state);

      void setRecordingState();
    void setPausedRecordingState();
    void setStoppedRecordingState();

    void selectInputDevice();
};

#endif // CAMERAVIEW_HPP

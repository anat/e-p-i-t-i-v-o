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

    public slots:
      void StartCam();
    void StopCam();
    void PauseCam();

    private slots:
    void recordCam();
    void stopRecCam();
    void pauseRecCam();

  private:
    Ui::CameraView *ui;
    vm::CameraVM* _vm;

    void setCameraConnects(bool state);

      void setRecordingState();
    void setPausedRecordingState();
    void setStoppedRecordingState();
};

#endif // CAMERAVIEW_HPP

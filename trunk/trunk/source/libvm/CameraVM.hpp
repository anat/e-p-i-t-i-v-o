#ifndef __CAMERAVM_HPP__
# define __CAMERAVM_HPP__

# include <QObject>
# include <QString>
# include <QImage>
# include <QLabel>

#include <cv.h>
#include <cv.hpp>
#include <cvaux.h>
#include <highgui.h>

namespace vm
{
  class CameraVM : public QObject
  {
    //TODO uncomment if slot or signals
    //Q_OBJECT

 public:
    static CameraVM* GetInstance();
    static void DelInstance();

    bool OpenDevice(QLabel* surface);

    void StartCam();
    void StopCam();

    //void PauseCapture();
    //void StopCapture();
    void SliderChangeValue();
    void FlipImage();


  protected:

  private:
    static CameraVM* _instance;

    CameraVM(); 
    ~CameraVM();

    IplImage* _iplImg;
    int _cameras;
//    bool _isFlip;
    bool _isStop;
    bool _breakCapture;

    QLabel * _surface;

    QImage ConvertIplImgtoQBitmpat(IplImage* img);
  };
}
#endif // !__CAMERAVM_HPP__

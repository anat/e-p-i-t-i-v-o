#include "CameraVM.hpp"
namespace vm
{
  CameraVM *CameraVM::_instance = 0;

  CameraVM::CameraVM()
  {
    _cameras = 0;
    //_isFlip = false;
    _isStop  = true;
    _breakCapture = true;
    //ui->containersFrame->setVisible(false);
  }
  CameraVM::~CameraVM()
  {
    delete _iplImg;
  }

  CameraVM* CameraVM::GetInstance()
  {
    if (!_instance)
      _instance = new CameraVM;
    return _instance;
  }

  void CameraVM::DelInstance()
  {
    if (_instance)
      delete _instance;
  }

  bool CameraVM::OpenDevice(QLabel *surface)
  {
    bool ret = true;
    _surface = surface;
    //this->StartCam();
    return ret;
  }

  void CameraVM::StartCam()
  {
    if(!_isStop)
      return;

    _isStop = false;
    _breakCapture = true;
    //ui->btnCapture->setText("Stop");
    CvCapture* capture = cvCaptureFromCAM(_cameras);
    if( !capture )
    {
      return;
    }
    IplImage* frame = 0;
    for(; _breakCapture;)
    {
      frame = cvQueryFrame( capture );
      if( !frame )
        break;
      //if(_isFlip)
       // cvFlip(frame, frame,1);

      if (_isStop)
        return;

      _iplImg = cvCloneImage(frame);
      QImage snapshot = ConvertIplImgtoQBitmpat(frame).scaled(_surface->size());
      _surface->setPixmap(QPixmap::fromImage(snapshot).scaled(_surface->size()));

      int t = cvWaitKey(40);
    }
  }

  void CameraVM::StopCam()
  {
    if (!_isStop)
    {
      _isStop = true;
      _breakCapture = false;
      //delete _surface;
    }
  }

  QImage CameraVM::ConvertIplImgtoQBitmpat(IplImage* img)
  {
    return QImage((const uchar *)img->imageData, img->width, img->height, QImage::Format_RGB888).rgbSwapped();
  }


  void CameraVM::SliderChangeValue()
  {
    IplImage* cloneImg = cvCloneImage(_iplImg);
    int p = 0;//ui->tbSlider->value();
    int w = cloneImg->width;
    int h = cloneImg->height;
    for(int i=0;i<h;i++)
    {
      for(int j=0;j<w;j++)
      {
        uchar* temp_ptr = &((uchar*)(cloneImg->imageData + cloneImg->widthStep*i))[j*3];
        int nVal =temp_ptr[0] + p;
        if (nVal < 0)
          nVal = 0;
        if (nVal > 255)
          nVal = 255;
        temp_ptr[0] = nVal;
        nVal =temp_ptr[1] + p;
        if (nVal < 0)
          nVal = 0;
        if (nVal > 255)
          nVal = 255;
        temp_ptr[1] = nVal;
        nVal =temp_ptr[2] + p;
        if (nVal < 0)
          nVal = 0;
        if (nVal > 255)
          nVal = 255;
        temp_ptr[2] = nVal;

      }
    }

    //QImage img = ConvertIplImgtoQBitmpat(cloneImg).scaled(this->size());
    //ui->lbImage->setPixmap(QPixmap::fromImage(img).scaled(ui->lbImage->size()));
  }

  void CameraVM::FlipImage()
  {
    //_isFlip = ui->cbFlip->isChecked();
  }
}

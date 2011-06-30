#include "CameraVM.hpp"
#include "VideoCodec.hpp"
#include <iostream>
namespace vm
{
  CameraVM *CameraVM::_instance = 0;

  CameraVM::CameraVM() :
    _iplImg(0),
    _record(0)
  {
    _cameras = 0;
    //_isFlip = false;
    _isStop  = true;
    _isPaused  = false;
    _record = 0;
    _isRecording = false;
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

  void CameraVM::mapSurface(QLabel *surface)
  {
    _surface = surface;// no delete
  }

  void CameraVM::StartCam()
  {
    VideoCodec *codec = new VideoCodec(640, 480, COLOR_BGR);

    if(!_isStop || !_surface)
    {
      if (_isPaused)
        _isPaused = false;
      return;
    }

    _isStop = false;
    CvCapture* capture = cvCaptureFromCAM(_cameras);
    //cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 10);
    //std::cout << "fps : " << fps << std::endl;
    if(capture)
    {
      IplImage* frame = 0;
      while(!_isStop)
      {
        if (_isStop)
          break;

        if (!_isPaused) //TODO THREAD SLEEP
        {
          frame = cvQueryFrame( capture );
          int buffSize = codec->encode((uint8_t *) frame->imageData);
          codec->decode((uint8_t *) frame->imageData);
          //::exit(1);
          if(!frame)
            break;

          //_iplImg = cvCloneImage(frame);
          QImage snapshot = ConvertIplImgtoQBitmpat(frame).scaled(_surface->size());
          _surface->setPixmap(QPixmap::fromImage(snapshot).scaled(_surface->size()));
          if (_isRecording)
            _record->AddVideoFrame(codec->getProcessedImg(), buffSize);
          cvWaitKey();
        }
        else
          cvWaitKey(350);
      }
      cvReleaseCapture(&capture);
    } // ~capture
  }

  void CameraVM::StopCam()
  {
    if (!_isStop)
    {
      _isStop = true;
      _surface->clear();
    }
  }

  void CameraVM::PauseCam()
  {
    if (!_isPaused)
    {
      _isPaused = true;
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
  }

  void CameraVM::StartRecordCam()
  {
    QString homePath = QDir::homePath();
    std::cout << "Start recording" << std::endl;
    if (!_record)
    {
      _record = new MediaFile(homePath+"/test.epitivo", true, Video);
      _record->Start();
      _isRecording = true;
    }
    
  }

  void CameraVM::StopRecCam()
  {
    std::cout << "Stop recording" << std::endl;
      _isRecording = false;
    if (_record)
    {
      _record->Stop();
      // save
      delete _record;
      _record = 0;
    }
  }

  void CameraVM::PauseRecCam()
  {
    std::cout << "Pause recording" << std::endl;
      _isRecording = false;

  }

}


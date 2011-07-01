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
    _isStop  = true;
    _isPaused  = false;
    _isRecording = false;
    _isPauseRecording = false;
  }
  CameraVM::~CameraVM()
  {
    delete _iplImg;
    delete _record;
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
    if(!_isStop || !_surface)
    {
      if (_isPaused)
        _isPaused = false;
      return;
    }

    _isStop = false;

    VideoCodec *codec = new VideoCodec(640, 480, COLOR_BGR);

    CvCapture* capture = cvCaptureFromCAM(_cameras);
    if(capture)
    {
      uint8_t * buff2  =  new uint8_t[640 * 480 * 3];
      IplImage* frame = 0;
      while(!_isStop)
      {
        if (_isStop)
          break;

        if (!_isPaused)
        {
          frame = cvQueryFrame( capture );
          if(!frame)
            break;

          if (_isRecording)
          {
            // dans tt les cas capture + enc + ecriture frame courante
            int buffSize = codec->encode((uint8_t *) frame->imageData);
            uint8_t* encImg = codec->getProcessedImg();
            _record->AddVideoFrame(encImg, buffSize);

            if (_isPauseRecording)
            {
              //  frame courante enc add au cache -> no refresh img
              std::cout << "Pause direct but recording" << std::endl;
              _cachedEncFrames.push(std::pair<int, uint8_t*>(buffSize, encImg));
            }
            else
            {
              // + capture + encodage frame courante
              if (_cachedEncFrames.size() > 0)
              {
                // recup de la plus vieille frame -> decodage -> affichage
                std::cout << "Delay playing while recording" << std::endl;
                std::pair<int, uint8_t*> const & cache = _cachedEncFrames.front();
                codec->setResultBuff(cache.second);
                codec->decode(buff2);
                QImage nFrame(buff2, 640, 480, QImage::Format_RGB888 );
                nFrame.scaled(_surface->size());
                _surface->setPixmap(QPixmap::fromImage(nFrame).scaled(_surface->size()));
                _cachedEncFrames.pop();
              }
              else
              {
                //  -> affichage
                std::cout << "Normal recording" << std::endl;
                QImage snapshot = ConvertIplImgtoQBitmpat(frame).scaled(_surface->size());
                _surface->setPixmap(QPixmap::fromImage(snapshot).scaled(_surface->size()));
              }
            }
          }
          else
          {
              QImage snapshot = ConvertIplImgtoQBitmpat(frame).scaled(_surface->size());
              _surface->setPixmap(QPixmap::fromImage(snapshot).scaled(_surface->size()));
          }
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
    if (!_record)
    {
      QString homePath = QDir::homePath();
      std::cout << "Start recording " << std::endl;
      _record = new MediaFile(homePath+"/test.epitivo", true, Video);
      _record->Start();
      _isRecording = true;
    }
    else if (_isPauseRecording)
    {
      _isPauseRecording = false;
    }
  }

  void CameraVM::StopRecCam()
  {
    std::cout << "Stop recording" << std::endl;
    _isRecording = false;
    _isPauseRecording = false;
    if (_record)
    {
      _record->Stop(); // save &clean
      delete _record;
      _record = 0;
    }
  }

  void CameraVM::PauseRecCam()
  {
    std::cout << "Pause recording" << std::endl;
    _isPauseRecording = true;
  }

}


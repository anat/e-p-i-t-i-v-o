#ifndef __PLAYERVM_HPP__
# define __PLAYERVM_HPP__

# include <QObject>
# include <QString>
# include <QImage>
# include <QLabel>
# include <QDir>
# include <QApplication>

#include <cv.h>
#include <cv.hpp>
#include <cvaux.h>
#include <highgui.h>

#include "app/MediaFile.hpp"
#include "VideoCodec.hpp"

namespace vm
{
  class PlayerVM : public QObject
  {
    //TODO uncomment if slot or signals
    //Q_OBJECT

      public slots:

 public:
    static PlayerVM* GetInstance();
    static void DelInstance();

    void mapSurface(QLabel* surface);

    void SliderChangeValue();

    void Play(int);
    void Stop();
    void Pause();
 bool _isStop;
    void setFilepath(QString const &);

  private:
    static PlayerVM* _instance;

    PlayerVM(); 
    ~PlayerVM();

    IplImage* _iplImg;

    bool _isPaused;

    QLabel * _surface;

    QImage ConvertIplImgtoQBitmpat(IplImage* img);

    QString _recordFilepath;
    MediaFile* _record;
    VideoCodec * _codec;
  };
}
#endif // !__PLAYERVM_HPP__

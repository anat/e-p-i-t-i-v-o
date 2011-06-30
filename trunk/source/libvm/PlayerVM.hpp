#ifndef __PLAYERVM_HPP__
# define __PLAYERVM_HPP__

# include <QObject>
# include <QString>
# include <QImage>
# include <QLabel>
# include <QDir>

#include <cv.h>
#include <cv.hpp>
#include <cvaux.h>
#include <highgui.h>

#include "app/MediaFile.hpp"

namespace vm
{
  class PlayerVM : public QObject
  {
    //TODO uncomment if slot or signals
    //Q_OBJECT

 public:
    static PlayerVM* GetInstance();
    static void DelInstance();

    void mapSurface(QLabel* surface);

    void SliderChangeValue();

    void Play();
    void Stop();
    void Pause();

    void setFilepath(QString const &);

  protected:

  private:
    static PlayerVM* _instance;

    PlayerVM(); 
    ~PlayerVM();

    IplImage* _iplImg;
    bool _isStop;
    bool _isPaused;

    QLabel * _surface;

    QImage ConvertIplImgtoQBitmpat(IplImage* img);

    QString _recordFilepath;
    MediaFile* _record;
  };
}
#endif // !__PLAYERVM_HPP__

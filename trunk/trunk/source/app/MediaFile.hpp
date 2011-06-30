#ifndef __MEDIAFILE_HPP__
# define __MEDIAFILE_HPP__

#include <QFile>
#include <QDataStream>
#include <QImage>
//#include <QThread>
//#include <QMutex>

#include <iostream>
#include <queue>
#include <stdint.h>

// 4096 - 8192 - 16384

const int ChunkSize = 16384;

enum MediaType { 
  Video, VideoAudio, Audio
};

struct Header_s
{
  unsigned char type; 

  unsigned long vFrameRate; 
  unsigned long vFrameCount;

  unsigned long aFrameRate;
  unsigned long aFrameCount;
};

struct FrameInfo_s
{
  unsigned long size; // frame size
  //unsigned long type; // chunk number
};

/*struct Chunk_s
{
  unsigned long size;
  unsigned long data[ChunkSize - sizeof(unsigned long)];
};*/

class MediaFile //: public QThread
{
  public:
    MediaFile(QString const & filepath, bool createMode, MediaType const & type);
    ~MediaFile();

    bool Start();
    bool Stop();

    //void run();

    bool AddVideoFrame(uint8_t * buff, int size);
    uint8_t* GetNextVideoFrame();
    //bool CloseMediaFile();

    //Header_s const& getFileHeader();
    //void setFileHeader(Header_s const& header);


  private:
    bool _createMode;

    QString _filepath;
    QFile* _file;
    QDataStream* _fileStream;

    Header_s* _fileHeader;

    char mediaType(MediaType const & type);

    bool initCreateMode(MediaType const& type);

    bool readHeader();
    bool writeHeader();

    //bool readFrame();
    //bool writeFrame();

    //std::queue<>
    //QMutex _taskLocker;
    //QMutex _Locker;
};

#endif // !__MEDIAFILE_HPP__

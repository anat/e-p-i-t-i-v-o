#include "MediaFile.hpp"


MediaFile::MediaFile(QString const & filepath, bool createMode, MediaType const & type) :
  _createMode(createMode),
  _fileHeader(0)
{
  _filepath = filepath;
  if (_createMode)
  {
    this->initCreateMode(type);
  }
}

MediaFile::~MediaFile()
{
  delete _fileHeader;
  delete _fileStream;
  delete _file;
}
 
bool MediaFile::initCreateMode(MediaType const & type)
{
  bool ret = true;
  
  _fileHeader = new Header_s;
  _fileHeader->type = this->mediaType(type);
  return ret;
}

bool MediaFile::Start()
{
  _file = new QFile(_filepath);
  if (_createMode )
  {
    if (!_file->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
      std::cerr << "Cannot open file for writing: "
        << qPrintable(_file->errorString()) << std::endl;
      return false;
    }
  }
  else if (!_file->open(QIODevice::ReadOnly))
  {
    std::cerr << "Cannot open file for reading: "
      << qPrintable(_file->errorString()) << std::endl;
    return false;
  }
  
  _fileStream = new QDataStream(_file);
  _fileStream->setVersion(QDataStream::Qt_4_7);

  if (_createMode)
    this->writeHeader();
  else
    this->readHeader();

  return true;
}

bool MediaFile::Stop()
{
  _file->close();
  delete _file;
  _file = 0;
}

char MediaFile::mediaType(MediaType const & type)
{
  if (type == Video)
    return '0';
  if (type == Audio)
    return '1';
  if (type == VideoAudio)
    return '2';
  return '0';
}

bool MediaFile::writeHeader()
{
  int bytes = _fileStream->writeRawData((char *)(_fileHeader), sizeof(Header_s));
  if (bytes != -1)
    return true;
  return false;
}

bool MediaFile::readHeader()
{
  Header_s * _fileHeader = new Header_s;
  int bytes = _fileStream->readRawData ((char *)(_fileHeader), sizeof(Header_s));
  //std::cout << "hread type: "<< header->type << std::endl;
  if (bytes != -1)
    return true;
  delete _fileHeader;
  _fileHeader = 0;
  return false;
}

// TODO REPLACE BY CONVERTED FRAME
bool MediaFile::AddVideoFrame(QImage const & img)
{
  bool ret = true;
  (*_fileStream) << img;
  return ret;
}

QImage* MediaFile::GetNextVideoFrame()
{
  QImage * img = new QImage;
  (*_fileStream) >> (*img);
  return img;
}

/*void MediaFile::run()
{

}*/

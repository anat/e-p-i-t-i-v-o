#include "CentralVM.hpp"

namespace vm
{
  CentralVM *CentralVM::_instance = 0;

  CentralVM::CentralVM() {}
  CentralVM::~CentralVM() {}

  CentralVM* CentralVM::GetInstance()
  {
    if (!_instance)
      _instance = new CentralVM;
    return _instance;
  }

  void CentralVM::DelInstance()
  {
    if (_instance)
      delete _instance;
  }

  void CentralVM::LoadFile(QString const & filePath)
  {
    _currentMediaPath = filePath;
  }

  void CentralVM::loadImage(QString const & filePath)
  {
  }
  void CentralVM::loadMusic(QString const & filePath)
  {
  }
  void CentralVM::loadVideo(QString const & filePath)
  {
  }

}

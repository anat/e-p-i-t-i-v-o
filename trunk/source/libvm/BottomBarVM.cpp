#include "BottomBarVM.hpp"
#include <iostream>

namespace vm
{
  BottomBarVM *BottomBarVM::_instance = 0;

  BottomBarVM::BottomBarVM() {}
  BottomBarVM::~BottomBarVM() {}

  BottomBarVM* BottomBarVM::GetInstance()
  {
    if (!_instance)
      _instance = new BottomBarVM;
    return _instance;
  }

  void BottomBarVM::DelInstance()
  {
    if (_instance)
      delete _instance;
  }

   	void BottomBarVM::Record()
	{
	}
   	void BottomBarVM::Play()
	{
	}
   	void BottomBarVM::Pause(){}
   	void BottomBarVM::Stop(){}
   	void BottomBarVM::Forward(){}
   	void BottomBarVM::Backward(){}

}

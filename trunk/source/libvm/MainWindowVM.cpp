#include "MainWindowVM.hpp"

namespace vm
{
  MainWindowVM *MainWindowVM::_instance = 0;

  MainWindowVM::MainWindowVM() {}
  MainWindowVM::~MainWindowVM() {}

  MainWindowVM* MainWindowVM::GetInstance()
  {
    if (!_instance)
      _instance = new MainWindowVM;
    return _instance;
  }

  void MainWindowVM::DelInstance()
  {
    if (_instance)
      delete _instance;
  }

}

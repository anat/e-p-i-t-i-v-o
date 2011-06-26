#include "MainWindowVM.hpp"
#include <iostream>

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

  bool MainWindowVM::openFile(QString const & filename)
  {
	  bool ret = true;
	  std::cout << "file :" << filename.toStdString();

	  return ret;
  }
}

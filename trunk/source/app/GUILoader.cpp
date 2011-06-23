#include <string>
#include "GUILoader.hpp"

static const QString AppName = "Epitivo";

GUILoader::GUILoader(int & argc, char ** argv) :
  QApplication(argc, argv)
{
	QCoreApplication::setApplicationName(AppName);
	Q_INIT_RESOURCE(resources);

	_mainWindow = new MainWindow;

  _mainVM = vm::MainWindowVM::GetInstance();
  _centralVM = vm::CentralVM::GetInstance();
  _bottomVM = vm::BottomBarVM::GetInstance();
}

GUILoader::~GUILoader()
{
  delete _mainWindow;
}

void GUILoader::Show()
{
  _mainWindow->show();
}


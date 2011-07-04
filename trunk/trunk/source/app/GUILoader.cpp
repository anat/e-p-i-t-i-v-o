#include <string>
#include "GUILoader.hpp"
#include <QDesktopWidget>
#include <QRect>

static const QString AppName = "Epitivo";

GUILoader::GUILoader(int & argc, char ** argv) :
  QApplication(argc, argv)
{
	QCoreApplication::setApplicationName(AppName);
	Q_INIT_RESOURCE(resources);

	_mainWindow = new MainWindow;

	_mainVM = vm::MainWindowVM::GetInstance();
	_centralVM = vm::CentralVM::GetInstance();
        _centralView = CentralView::GetInstance();
	_cameraVM = vm::CameraVM::GetInstance();
	_playerVM = vm::PlayerVM::GetInstance();
        _playListVM = PlayListWidget::GetInstance();
        QDesktopWidget bureau;
        QRect surface_bureau = bureau.screenGeometry();
        int x = surface_bureau.width()/2 - _mainWindow->width()/2;
        int y = surface_bureau.height()/2 - _mainWindow->height()/2;
        y -= (int)y*0.2;
        _mainWindow->move(x,y);
}

GUILoader::~GUILoader()
{
  delete _mainWindow;
}

void GUILoader::Show()
{
  _mainWindow->show();
}


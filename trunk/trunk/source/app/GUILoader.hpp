#ifndef __GUILOADER_HPP__
# define __GUILOADER_HPP__

# include <QApplication>
# include <QString>
# include "libview/MainWindow.hpp"
# include "libvm/MainWindowVM.hpp"
# include "libvm/CentralVM.hpp"
#include "libvm/BottomBarVM.hpp"

class GUILoader : public QApplication
{
  public:
    GUILoader(int & argc, char ** argv);
    ~GUILoader();

    void Show();

  private:
    MainWindow* _mainWindow;
    vm::MainWindowVM* _mainVM;
    vm::CentralVM* _centralVM;
    vm::BottomBarVM* _bottomVM;
};

#endif // !__GUILOADER_HPP__

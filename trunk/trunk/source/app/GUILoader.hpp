#ifndef __GUILOADER_HPP__
# define __GUILOADER_HPP__

# include <QApplication>
# include <QString>
# include "libview/MainWindow.hpp"

class GUILoader : public QApplication
{
  public:
    GUILoader(int & argc, char ** argv);
    ~GUILoader();

    void Show();

  private:
	  MainWindow* _mainWindow;
};

#endif // !__GUILOADER_HPP__

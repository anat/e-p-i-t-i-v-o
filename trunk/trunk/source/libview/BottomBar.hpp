#ifndef BOTTOMBAR_HPP
#define BOTTOMBAR_HPP

#include <QWidget>

#include "libvm/BottomBarVM.hpp"

namespace Ui {
    class BottomBar;
}

class BottomBar : public QWidget
{
  Q_OBJECT

  public:
    explicit BottomBar(QWidget *parent = 0);
    ~BottomBar();

    private slots:
      void record();
    void play();
    void pause();
    void stop();
    void forward();
    void backward();

  private:
    Ui::BottomBar *ui;

    vm::BottomBarVM* _dataContext;

    void setQtConnects();
};

#endif // BOTTOMBAR_HPP

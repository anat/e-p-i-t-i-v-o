#ifndef CENTRALVIEW_HPP
#define CENTRALVIEW_HPP

#include <QWidget>
#include <QString>
#include "CentralView.hpp"
# include "libvm/CentralVM.hpp"

namespace Ui {
  class CentralView;
}

class CentralView : public QWidget
{
  Q_OBJECT

public:
  explicit CentralView(QWidget *parent = 0);
	  ~CentralView();

private:
  Ui::CentralView *ui;

  vm::CentralVM* _dataContext;

};

#endif // CENTRALVIEW_HPP

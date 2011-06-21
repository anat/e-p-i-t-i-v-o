#include "CentralView.hpp"
#include "ui_CentralView.h"

CentralView::CentralView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CentralView)
{
  ui->setupUi(this);
  _dataContext = vm::CentralVM::GetInstance();
}

CentralView::~CentralView()
{
  delete ui;
}

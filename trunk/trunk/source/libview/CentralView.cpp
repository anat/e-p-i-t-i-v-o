#include "CentralView.hpp"
#include "ui_CentralView.h"

CentralView::CentralView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CentralView)
{
  ui->setupUi(this);
  _dataContext = vm::CentralVM::GetInstance();

  _bottomBar = new BottomBar(this);

  ui->mainGridLayout->addWidget(_bottomBar, 1, 0, 1, 3, Qt::AlignJustify);
}

CentralView::~CentralView()
{
  delete ui;
}


#include "BottomBar.hpp"
#include "ui_BottomBar.h"

BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);
}

BottomBar::~BottomBar()
{
    delete ui;
}

void BottomBar::setQtConnects()
{
  //connect(ui->recordButton, SIGNAL(clicked()), this, SLOT(record()));
  connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
  connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
  connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
  connect(ui->backwardButton, SIGNAL(clicked()), this, SLOT(backward()));
  connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(forward()));
}

   	void BottomBar::record() {}
   	void BottomBar::play() {}
   	void BottomBar::pause() {}
   	void BottomBar::stop() {}
   	void BottomBar::forward() {}
   	void BottomBar::backward() {}

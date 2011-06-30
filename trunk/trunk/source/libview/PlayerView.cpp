#include "PlayerView.hpp"
#include "ui_PlayerView.h"

PlayerView::PlayerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerView)
{
    ui->setupUi(this);

  _vm = vm::PlayerVM::GetInstance();
  _vm->mapSurface(ui->imgBoxLabel2);
}

PlayerView::~PlayerView()
{
   delete ui;
}

void PlayerView::Play()
{
  _vm->Play();
}

void PlayerView::Pause()
{
  _vm->Pause();
}

void PlayerView::Stop()
{
  _vm->Stop();
}

    void PlayerView::setFilepath(QString const & file)
    {
      _vm->setFilepath(file);
    }

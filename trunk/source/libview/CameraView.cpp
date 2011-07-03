#include "CameraView.hpp"
#include "ui_CameraView.h"
#include <iostream>

#include <sstream>

CameraView::CameraView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraView)
{
    ui->setupUi(this);




  _vm = vm::CameraVM::GetInstance();
  _vm->mapSurface(ui->imgBoxLabel);

 //this->selectInputDevice();


}

CameraView::~CameraView()
{
    _vm->DelInstance();
    delete ui;
}

void CameraView::StartCam()
{
  _vm->StartCam();
}

void CameraView::StopCam()
{
  _vm->StopCam();
}


void CameraView::recordCam()
{
  _vm->StartRecordCam();
}

void CameraView::stopRecCam()
{
  _vm->StopRecCam();
}

void CameraView::pauseRecCam()
{
  _vm->PauseRecCam();
}
void CameraView::selectInputDevice()
{
  QDialog dialog;

  QPushButton buttonAccept("OK");
    QPushButton buttonReject("Cancel");
  QComboBox combo;
    QLabel label("Device : ");
  std::set<int> const & cams = _vm->getCamDevices();
  std::set<int>::const_iterator it;

    combo.addItem("0");
  for ( it=cams.begin() ; it != cams.end(); it++ )
  {
    int val = *it;
    std::string s;
    std::stringstream out;
    out << val;
    s = out.str();
    QString qstr(s.c_str());
    combo.addItem(qstr);
  }


  connect(&buttonAccept, SIGNAL(clicked()), &dialog, SLOT(accept()));
  connect(&buttonReject, SIGNAL(clicked()), &dialog, SLOT(reject()));

  QVBoxLayout layout;
  QHBoxLayout layout1;
  QHBoxLayout layout2;

  layout1.addWidget(&label);
  layout1.addWidget(&combo);

  layout2.addWidget(&buttonReject);
  layout2.addWidget(&buttonAccept);

  layout.addItem(&layout1);
  layout.addItem(&layout2);

  std::cout << "ddddddddddd" << std::endl;
  dialog.setLayout(&layout);
  dialog.exec();
  std::cout << "ddddddddffffffffffff" << std::endl;
  if (dialog.result() == QDialog::Accepted)
  {
    _selected = combo.currentText();
    _vm->_cameras = atoi((_selected.toStdString()).c_str());
    std::cout << "C" << std::endl;
  }
  else
      _vm->_cameras = 0;
  std::cout << "mmmm" << std::endl;
}

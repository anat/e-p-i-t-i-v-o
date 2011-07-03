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
    _isRecording = false;
    _isCamActive = false;
}

CameraView::~CameraView()
{
    _vm->DelInstance();
    delete ui;
}

void CameraView::StartCam()
{
    std::cout << "Start Cam ";
    if (!_isCamActive)
    {
         _isCamActive = true;
        std::cout << "Ok" << std::endl;
        _vm->StartCam();

    }
    else if (_isRecording)
    {
        _vm->StartRecordCam(); // reprise sur rec
    }
    else
         std::cout << "Ko" << std::endl;
}

void CameraView::StopCam()
{
    std::cout << "StopCam Cam ";
    if (!_isCamActive)
    {
        _isCamActive = false;
        std::cout << "Ok" << std::endl;
        _vm->StopCam();
    }
    else
         std::cout << "Ko" << std::endl;
}


void CameraView::recordCam()
{
    if (_isCamActive && !_isRecording)
    {
        _isRecording = true;
      _vm->StartRecordCam();
    }
}

void CameraView::stopRecCam()
{
    if (_isRecording)
    {
        _isRecording = false;
      _vm->StopRecCam();
    }
    else if (_isCamActive)
    {
        _vm->StopCam();
    }
}

void CameraView::pauseRecCam()
{
    if (_isCamActive)
    {
        _vm->PauseRecCam();
    }
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

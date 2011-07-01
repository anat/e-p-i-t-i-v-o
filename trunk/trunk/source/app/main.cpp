#include <string>

#include "GUILoader.hpp"
#include "ConfigManager.hpp"

//test cam
#include  <set>
#include  <iostream>
#include <cv.h>
#include <cv.hpp>
#include <cvaux.h>
#include <highgui.h>

using namespace vm;

const std::string EpitivoConfFile = "epitivo.conf.xml";

std::set<int> getCamDevices() 
{
  std::set<int> setDispos;
  CvCapture* capTmp;
  int camCount = 0;
  for (int i = 0; camCount < sizeof (1000); i++) {
    capTmp = cvCreateCameraCapture(i);
    if (capTmp) {
      setDispos.insert(i);
      cvReleaseCapture(&capTmp);
      std::cout << i << " dispo" << std::endl;
      camCount++;
    } else {
      //std::cout << i << " pas disso" << std::endl;
    }
  }
  return setDispos;
}

int main(int argc, char** argv)
{
  //ConfigManager config(EpitivoConfFile);

  GUILoader gui(argc, argv);

  gui.Show();

  return gui.exec();
  getCamDevices();
}


#include <string>

#include "GUILoader.hpp"
#include "ConfigManager.hpp"

//test cam
/*#include  <set>
#include  <iostream>
#include <cv.h>
#include <cv.hpp>
#include <cvaux.h>
#include <highgui.h>
*/
using namespace vm;

const std::string EpitivoConfFile = "epitivo.conf.xml";

int main(int argc, char** argv)
{
  //ConfigManager config(EpitivoConfFile);

  GUILoader gui(argc, argv);


  gui.Show();

  return gui.exec();
  //getCamDevices();
}


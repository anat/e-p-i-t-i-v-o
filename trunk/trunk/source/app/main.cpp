#include <string>

#include "GUILoader.hpp"
#include "ConfigManager.hpp"

using namespace vm;

const std::string EpitivoConfFile = "epitivo.conf.xml";

int main(int argc, char** argv)
{
  //ConfigManager config(EpitivoConfFile);

  GUILoader gui(argc, argv);

  gui.Show();

  return gui.exec();
}


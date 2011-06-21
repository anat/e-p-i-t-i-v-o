#include "ConfigManager.hpp"

std::string const FileLoadError = "Failed to load file.";

QString const ConfigManager::LibrariesTagName = "libraries";
QString const ConfigManager::LibraryTagName = "library";
QString const ConfigManager::PlaylistTagName = "playlist";
QString const ConfigManager::MediaTagName = "library";

QString const ConfigManager::VideoAttr = "video";
QString const ConfigManager::AudioAttr = "audio";
QString const ConfigManager::PictureAttr = "picture";
QString const ConfigManager::PlaylistAttr = "playlist";
QString const ConfigManager::UnknowAttr = "unknow";

ConfigManager::ConfigManager(std::string const & filepath) :
    _configFilePath(filepath.c_str())
{
  this->loadConfigFile();
}

bool ConfigManager::loadConfigFile()
{
  QFile file(_configFilePath);

  if(!file.open(QIODevice::ReadOnly))
  {
    //QMessageBox::warning( this, "Loading", "Failed to load file." );
    std::cout << FileLoadError;
    return false;
  }
  //TODO load the xml file
  return false;
}

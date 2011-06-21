#ifndef CONFIGMANAGER_HPP
# define CONFIGMANAGER_HPP

# include <string>
# include <iostream>
# include <QFile>
# include <QString>
# include <QMessageBox>

enum ELibraryType {
  LibVideo_e, LibAudio_e, LibPicture_e, LibPlaylist_e, LibRecorded_e
};
enum EMediaType {
  MediaUnknow_e, MediaVideo_e, MediaAudio_e, MediaPicture_e, MediaPlaylist_e
};

class ConfigManager
{
public:
  static QString const  LibrariesTagName;
  static QString const  LibraryTagName;
  static QString const  PlaylistTagName;
  static QString const  MediaTagName;

  static QString const  VideoAttr;
  static QString const  AudioAttr;
  static QString const  PictureAttr;
  static QString const  PlaylistAttr;
  static QString const  UnknowAttr;

  ConfigManager(std::string const & filepath);


private:

  QString    _configFilePath;

  bool loadConfigFile();

};

#endif // CONFIGMANAGER_HPP

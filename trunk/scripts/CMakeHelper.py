#!/usr/bin/python

import os
import shutil

class CMakeHelper:

  _tempFiles = [ 
    "Makefile", 
    "CMakeFiles", 
    "cmake_install.cmake", 
    "CMakeCache.txt" 
  ]
  _rootDir = ""
  _cleanedFolders = []
  _cleanedFiles = []

  def __init__(self, rootDir):
    self._rootDir = rootDir

  def cleanTempFiles(self, dirPath):

    for curFile in self._tempFiles:
      filepathToClean = dirPath+curFile

      if os.path.isdir(filepathToClean):
        shutil.rmtree(filepathToClean)
        self._cleanedFolders.append(filepathToClean)

      elif os.path.isfile(filepathToClean):
        os.remove(filepathToClean)
        self._cleanedFiles.append(filepathToClean)
  
  def cleanR(self, dirPath):
    curDirPath = dirPath+"/"
    dirList = []

    self.cleanTempFiles(curDirPath)

    for curFile in os.listdir(curDirPath):
      curFilePath = curDirPath+curFile

      if curFile[0] != "." and os.path.isdir(curFilePath):
        dirList.append(curFilePath)

    for curDir in dirList:
      self.cleanR(curDir)

  def cleanAll(self):
    self.cleanR(self._rootDir)

  def showCleaned(self):
    print "Directory cleaned:"
    for cur in self._cleanedFolders:
      print "  "+cur
    print "File cleaned:"
    for cur in self._cleanedFiles:
      print "  "+cur

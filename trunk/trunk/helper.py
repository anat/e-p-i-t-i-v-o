#!/usr/bin/python

import sys
import commands

CMakeRootDir = "."
SourceDir = "source"
ScriptDir = "scripts"

sys.path.append(ScriptDir)
from CMakeHelper import *

##
## Script
##
argc = len(sys.argv)

if argc > 2:

  if sys.argv[1] == "cmake":
    cmHelper = CMakeHelper(SourceDir)

    if (sys.argv[2] == "ca"):
      cmdStatus,cmdOutput = commands.getstatusoutput("make clean")
      cmdStatus,cmdOutput = commands.getstatusoutput("rm -rf source/bin")
      print "Builds cleaned."
      cmdStatus,cmdOutput = commands.getstatusoutput("rm -rf source/epitivo.dir")
      print "Bin cache cleaned."
      cmHelper.cleanTempFiles(CMakeRootDir+"/")
      cmHelper.cleanAll()
      cmHelper.showCleaned()

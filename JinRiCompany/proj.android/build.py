#!/usr/bin/env python

import os
import re
import sys

def Start_Build(debug, install=False):
	print "Start_Build:", debug, install
	APP_DIR = os.getcwd()
	print "current dir is:", APP_DIR
	
	names = re.split('\\\\', APP_DIR)
	APP_NAME = names[len(names)-2]
	print "current app name is:", APP_NAME
	
	APP_CYGWIN_DIR = "/cygdrive/" + APP_DIR.replace(":\\", "/").replace("\\", "/")
	print "cygwin dir is:", APP_CYGWIN_DIR
	
	BUILD_FILE_SH = "build_native.sh"
	if os.path.exists(BUILD_FILE_SH) is False:
		print "File %s doesn't exist"%(BUILD_FILE_SH)
		return -1
	
	COCOS2DX_ENGINE_JAVA_ROOT = APP_DIR + "/../../../cocos2dx/platform/android/java"
	if os.path.exists(BUILD_FILE_SH) is False:
		print "folder %s doesn't exist"%(COCOS2DX_ENGINE_JAVA_ROOT)
		return -1

	print "begin check tools...."
	ANDROID_TOOLS_ROOT = APP_DIR + "\\..\\..\\..\\..\\android-dev\\"
	if os.path.exists(ANDROID_TOOLS_ROOT) is False:
		print "you should update svn and get the android-dev folder: ", ANDROID_TOOLS_ROOT
		return -1
	
	CYGWIN_BIN = ANDROID_TOOLS_ROOT + "cygwin\\bin\\bash.exe"
	if os.path.exists(CYGWIN_BIN) is False:
		print "you should update svn and get the android-dev folder: ", CYGWIN_BIN
		return -1
		
	ANT_BIN	= ANDROID_TOOLS_ROOT + "apache-ant-1.9.0\\bin\\ant"
	if os.path.exists(ANT_BIN) is False:
		print "you should update svn and get the android-dev folder: ", ANT_BIN
		return -1
		
	ANDROID_SDK_TOOLS = ANDROID_TOOLS_ROOT + "android-sdk\\tools\\android.bat"
	if os.path.exists(ANDROID_SDK_TOOLS) is False:
		print "you should update svn and get the android-dev folder: ", ANDROID_SDK_TOOLS
		return -1
	
	ADB_TOOLS = ANDROID_TOOLS_ROOT + "android-sdk\\platform-tools\\adb.exe"
	if os.path.exists(ANDROID_SDK_TOOLS) is False:
		print "you should update svn and get the android-dev folder: ", ADB_TOOLS
		return -1
		
	SUBDIR = "x86"
	if os.environ['PROGRAMFILES'].find('86') > 0:
		SUBDIR = "x64"
	
	NDK_ROOT = ANDROID_TOOLS_ROOT + "android-ndk-r8e/%s"%(SUBDIR)
	if os.path.exists(NDK_ROOT) is False:
		print "you should update svn and get the android-dev folder: ",NDK_ROOT
		return -1
		
	NDK_ROOT = "/cygdrive/" + NDK_ROOT.replace(":\\", "/").replace("\\", "/")
	print "tools check ok...."
		
	os.system('''%s --login -c "export NDK_ROOT=%s && cd %s && ./%s"'''%(CYGWIN_BIN, NDK_ROOT, APP_CYGWIN_DIR, BUILD_FILE_SH))
	os.system("%s update project -p ./"%(ANDROID_SDK_TOOLS))
	os.system("%s update project -p %s"%(ANDROID_SDK_TOOLS, COCOS2DX_ENGINE_JAVA_ROOT))
	
	os.system("%s %s"%(ANT_BIN, debug))
	
	if install is True:
		os.system("%s install -r bin\\%s-%s.apk"%(ADB_TOOLS, APP_NAME, debug))
		
	return 1

if __name__ == '__main__':
	debug = 'debug'
	if len(sys.argv) > 1:
		debug = sys.argv[1]

	install = False
	if len(sys.argv) > 2:
		if sys.argv[2] == "yes" :
			install = True
		
	Start_Build(debug, install)
	



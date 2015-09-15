#! /usr/bin/env python
import os
import string
import shutil
import subprocess
#set texture packer path
#PATH_TEXTURE_PACKER = "c:/progra~2/codeandweb/texturepacker/bin/"
PATH_TEXTURE_PACKER = ""
PATH_RES = "./res/"
PATH_JSON_COCOS_STUDIO = "./uis/Export/uis/"
JSON_COCOS_STUDIO_EXT = "ExportJson"
BG_FOLDER = "bg"
NOPACK_FOLDER = "noPack"
DEST_PATH_RES = "./Resources/"
DEST_PATH_RES_SHARED = "./Resources/shared/"
VER = "3.0.9"
#VER = "3.3.4"

def buildTexureAtlas(name, isFolder, noAlpha) :
	if not isFolder :
		length = len(name)
		nameOut = name[:length-4]
		idx = string.index(nameOut,"/")
		nameOut = nameOut[idx:]
	else :
		nameOut = name
	if VER[2:3] == "0" :
		cmd = PATH_TEXTURE_PACKER + "texturepacker --force-identical-layout --content-protection fc5cc0ed15b97c4251ce7d9e3e26102b --pack-mode Best --dither-fs-alpha --reduce-border-artifacts --texture-format pvr2ccz --sheet " + DEST_PATH_RES + nameOut + "@4x.pvr.ccz --data " + DEST_PATH_RES + nameOut + "@4x.plist --format cocos2d --max-width 4096 --max-height 4096 --main-extension \"@4x.\" "
		if noAlpha :
			cmd += "--autosd-variant 0.25:\"@1x.\":allowfraction:1024 --autosd-variant 0.5:\"@2x.\":allowfraction:2048 --opt RGB565 --size-constraints NPOT --algorithm MaxRects " +  PATH_RES + name
		else :
			cmd += "--autosd-variant 0.25:\"@1x.\":allowfraction:1024 --autosd-variant 0.5:\"@2x.\":allowfraction:2048 --opt RGBA4444 --size-constraints NPOT --algorithm MaxRects " +  PATH_RES + name
	else :
		cmd = PATH_TEXTURE_PACKER + "texturepacker --force-identical-layout --pack-mode Best --content-protection fc5cc0ed15b97c4251ce7d9e3e26102b --dither-fs-alpha --reduce-border-artifacts --texture-format pvr2ccz --sheet " + DEST_PATH_RES + nameOut + "@{v}x.pvr.ccz --data " + DEST_PATH_RES + nameOut + "@{v}x.plist --format cocos2d "
		if noAlpha :
			cmd += "--variant 1:\"4\"::4096:4096 --variant 0.25:\"1\" --variant 0.5:\"2\" --opt RGB565 --size-constraints NPOT --algorithm MaxRects " +  PATH_RES + name
		else :
			cmd += "--variant 1:\"4\"::4096:4096 --variant 0.25:\"1\" --variant 0.5:\"2\" --opt RGBA4444 --size-constraints NPOT --algorithm MaxRects " +  PATH_RES + name
	print PATH_RES + name
	subprocess.call(cmd, shell=True)

# build all folder in PATH_RES
for root, dirs, filenames in os.walk(PATH_RES):	
	for dir in dirs:		
		if dir != BG_FOLDER and dir != NOPACK_FOLDER:
			buildTexureAtlas(dir, True, False)
	break
# move newly create res to multi folder
# os.chdir(DEST_PATH_RES)
# list = ["@4x","@3x","@2x","@1.5x","@1x"]
list = ["@4x","@2x","@1x"]
for suffix in list:
	if not os.path.exists(DEST_PATH_RES+suffix):
		os.makedirs(DEST_PATH_RES+suffix)
	for root, dirs, filenames in os.walk(DEST_PATH_RES):
		plistfile = suffix+".plist"
		cczfile = suffix+".pvr.ccz"
		for f in filenames:			
			if (plistfile in f):
				newname = string.replace(f,suffix,"")
				shutil.copy(DEST_PATH_RES+f,DEST_PATH_RES+suffix+"/"+newname)
				os.remove(DEST_PATH_RES+f)
			elif (cczfile in f):
				newname = string.replace(f,suffix,"")
				shutil.copy(DEST_PATH_RES+f,DEST_PATH_RES+suffix+"/"+newname)				
				os.remove(DEST_PATH_RES+f)				
raw_input("############ Build done ############")
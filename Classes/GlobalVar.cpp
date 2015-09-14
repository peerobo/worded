//
//  GlobalVar.cpp
//  fPlay
//
//  Created by Duc_NH on 5/6/14.
//
//

#include "GlobalVar.h"

cocos2d::Layer* GlobalVar::curScene = NULL;
sMyData GlobalVar::myData = {
	false, // fb
	true,	// audio
	true,	// vibration
};
void* GlobalVar::gameLogic = NULL;
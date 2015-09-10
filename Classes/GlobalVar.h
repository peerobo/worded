//
//  GlobalVar.h
//  fPlay
//
//  Created by Duc_NH on 5/6/14.
//
//

#ifndef __fPlay__GlobalVar__
#define __fPlay__GlobalVar__
#include "cocos2d.h"
USING_NS_CC;

struct sMyData{	
    bool isFb;
	bool isEnableAudio;	
	bool isEnableVibration;
};

class GlobalVar {
public:
	/////////////////////////////////////	
    static cocos2d::Layer* curScene;	
	static sMyData myData;
/////////////////////////////////////
};

#endif /* defined(__fPlay__GlobalVar__) */

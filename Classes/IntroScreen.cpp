//
//  IntroScreen.cpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/1/15.
//
//

#include <stdio.h>
#include "IntroScreen.h"
#include "base/Util.h"
#include "Constants.h"
#include "intro/IntroItem.h"

IntroScreen::IntroScreen()
{
    auto bg = util_getSpriteFromImageJPG(Constants::ASS_BG_INTRO);
    Size s = util_getScreenSize();
    bg->setPosition(s.width/2,s.height/2);
    addChild(bg);
    
//    Vector<FiniteTimeAction*> v;
//    v.pushBack(DelayTime::create(0.7f));
//    v.pushBack(CallFunc::create(CC_CALLBACK_0(IntroScreen::startIntro, this)));
//    runAction(Sequence::create(v));
    startIntro();
}

void IntroScreen::startIntro()
{
    Configuration* cfg = Configuration::getInstance();
    Size s = util_getScreenSize();
    float posY = s.height/2;
    
    IntroItem* item = IntroItem::create();
    item->setValue(cfg->getValue("onemode").asString(), nullptr);
    addChild(item);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-100);
    item->runIn(0);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("tablemode").asString(), nullptr);
    addChild(item);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-250);
    item->runIn(1);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("leaderboard").asString(), nullptr);
    addChild(item);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-400);
    item->runIn(2);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("more").asString(), nullptr);
    addChild(item);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-550);
    item->runIn(3);

}
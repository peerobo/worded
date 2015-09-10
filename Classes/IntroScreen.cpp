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
#include "onemode/OneScreen.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "AppTrackerWrapper.h"
#endif

void IntroScreen::onOneMode()
{
	util::graphic::changeSceneWithLayer(OneScreen::create());
	
}

void IntroScreen::onTableMode()
{
    
}

void IntroScreen::onLeaderboard()
{
    
}

void IntroScreen::onMoreGame()
{
    util::ad::showVungle();
}

void IntroScreen::onTouchItem(int type)
{
    if (type == 0 || type == 1) {
        
        // buttons vanish
        int count = 0;
        for (int i =0; i<4; i++) {
            auto node = dynamic_cast<IntroItem*>(getChildByTag(10+i));
            if(i!=type)
            {
                node->runOut(count);
                count++;
            }
            else
            {
                node->fadeOut();
            }
        }
        // cache next bg
        auto bg = util::graphic::getSpriteFromImageJPG(type == 0 ? Constants::ASS_BG_ONE:Constants::ASS_BG_TABLE);
        Size s = util::graphic::getScreenSize();
        bg->setPosition(s.width/2,s.height/2);
        addChild(bg,0);
        
        // bg fade out
        Vector<FiniteTimeAction*> v;
        v.pushBack(FadeOut::create(1.5f));
        v.pushBack(CallFunc::create(CC_CALLBACK_0(IntroScreen::processType, this,type)));
        getChildByTag(1)->runAction(Sequence::create(v));
        
    }
    else
    {
        // blink only
        auto node = dynamic_cast<IntroItem*>(getChildByTag(10+type));
        node->blink();
        processType(type);
    }
}

void IntroScreen::processType(int type)
{
    switch (type) {
        case 0:
            onOneMode();
            break;
        case 1:
            onTableMode();
            break;
        case 2:
            onLeaderboard();
            break;
        case 3:
            onMoreGame();
            break;
        default:
            break;
    }
}

IntroScreen::IntroScreen()
{
    auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_INTRO);
    Size s = util::graphic::getScreenSize();
    bg->setPosition(s.width/2,s.height/2);
    addChild(bg,1);
    bg->setTag(1);
    
	util::common::playMusic(Constants::ASS_SND_THEME);

//    Vector<FiniteTimeAction*> v;
//    v.pushBack(DelayTime::create(0.7f));
//    v.pushBack(CallFunc::create(CC_CALLBACK_0(IntroScreen::startIntro, this)));
//    runAction(Sequence::create(v));
    startIntro();
}

void IntroScreen::startIntro()
{
    Configuration* cfg = Configuration::getInstance();
    Size s = util::graphic::getScreenSize();
    float posY = s.height/2;
    
    IntroItem* item = IntroItem::create();
    item->setValue(cfg->getValue("onemode").asString(), CC_CALLBACK_0(IntroScreen::onTouchItem, this,0));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-100);
    item->setTag(10);
    item->runIn(0);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("tablemode").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,1));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-250);
    item->runIn(1);
    item->setTag(11);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("leaderboard").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,2));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-400);
    item->runIn(2);
    item->setTag(12);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("more").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,3));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-550);
    item->runIn(3);
    item->setTag(13);
}
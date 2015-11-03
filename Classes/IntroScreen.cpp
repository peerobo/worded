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
#include "learn/LearnScreen.h"
#include "tablemode/CatChooser.h"
#include "gui/SettingGUI.h"
#include "gui/AlertGUI.h"
#include "matching/MatchingScreen.h"
#include "matching/MatchingLogic.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "AppTrackerWrapper.h"
#endif

void IntroScreen::onLearnMode()
{
	util::graphic::changeSceneWithLayer(LearnScreen::create());
	
}

void IntroScreen::onMore()
{
    Configuration* cfg = Configuration::getInstance();
    Size s = util::graphic::getScreenSize();
    float posY = s.height/2 + 150;
    
    IntroItem* item = IntroItem::create();
    item->setValue(cfg->getValue("back").asString(), CC_CALLBACK_0(IntroScreen::onTouchItem, this,4));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-100);
    item->setTag(14);
    item->runIn(0);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("leaderboard").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,5));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-250);
    item->runIn(1);
    item->setTag(15);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("rate").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,6));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-400);
    item->runIn(2);
    item->setTag(16);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("moreGames").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,7));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-550);
    item->runIn(3);
    item->setTag(17);
}

void IntroScreen::onBack()
{
    startIntro();
}

void IntroScreen::onTableMode()
{
    util::graphic::changeSceneWithLayer(CatChooser::create());
}

void IntroScreen::onPuzzleMode()
{
	// init logic
	(new MatchingLogic())->init();
	util::graphic::changeSceneWithLayer(MatchingScreen::create());
}

void IntroScreen::onLeaderboard()
{
    if(util::platform::isGC())
    {
        util::platform::showGC();
    }
    else
    {
        auto alert = AlertGUI::create();
        alert->setMsg(Configuration::getInstance()->getValue("gcdisable").asString());
        alert->show();
    }
}

void IntroScreen::onRate()
{
    util::platform::rate();
}

void IntroScreen::onSetting()
{
	SettingGUI::create()->show();
}

void IntroScreen::onMoreGame()
{
    util::ad::showLeadboltAd();
}

void IntroScreen::onTouchItem(int type)
{
    auto node = dynamic_cast<IntroItem*>(getChildByTag(10+type));
    if(node->getOpacity() < 255)
        return;
	util::common::playSound(Constants::ASS_SND_CLICK, false);
    if (type == 0 || type == 1 || type == 3 || type == 4 || type == 8)
    {
        
        // buttons vanish
        int count = 0;
        for (int i =0; i<9; i++) {
            auto node = dynamic_cast<IntroItem*>(getChildByTag(10+i));
            if(node)
            {
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
            
        }
        if (type == 0 || type == 1 || type == 8) {
            // cache next bg
			const char* bgStr = NULL;
			switch (type)
			{
			case 0:
				bgStr = Constants::ASS_BG_ONE;
				break;
			case 1:
				bgStr = Constants::ASS_BG_TABLE;
				break;
			case 8:
				bgStr = Constants::ASS_BG_MATCHING;
				break;
			default:
				break;
			}
            auto bg = util::graphic::getSpriteFromImageJPG(bgStr);
            Size s = util::graphic::getScreenSize();
            bg->setPosition(s.width/2,s.height/2);
            addChild(bg,0);
            
            // bg fade out
            Vector<FiniteTimeAction*> v;
            v.pushBack(FadeOut::create(0.7f));
            v.pushBack(CallFunc::create(CC_CALLBACK_0(IntroScreen::processType, this,type)));
            getChildByTag(1)->runAction(Sequence::create(v));

        }
        else
        {
            processType(type);
        }
        
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
            onLearnMode();
            break;
        case 1:
            onTableMode();
            break;
        case 2:
            onSetting();
            break;
        case 3:
            onMore();
            break;
		case 4:
            onBack();
			break;
        case 5:
            onLeaderboard();
            break;
        case 6:
            onRate();
            break;
        case 7:
            onMoreGame();
            break;
		case 8:
			onPuzzleMode();
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
    float posY = s.height/2 + 150;
    
    IntroItem* item = IntroItem::create();
    item->setValue(cfg->getValue("learn").asString(), CC_CALLBACK_0(IntroScreen::onTouchItem, this,0));
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
	item->setValue(cfg->getValue("puzzlemode").asString(), CC_CALLBACK_0(IntroScreen::onTouchItem, this, 8));
	addChild(item, 1);
	item->setPositionX(s.width / 2);
	item->setPositionY(posY - 400);
	item->runIn(2);
	item->setTag(18);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("setting").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,2));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-550);
    item->runIn(3);
    item->setTag(12);
    
    item = IntroItem::create();
    item->setValue(cfg->getValue("more").asString(),  CC_CALLBACK_0(IntroScreen::onTouchItem, this,3));
    addChild(item,1);
    item->setPositionX(s.width/2);
    item->setPositionY(posY-700);
    item->runIn(4);
    item->setTag(13);
//
//	item = IntroItem::create();
//	item->setValue(cfg->getValue("setting",Value("Settings")).asString(), CC_CALLBACK_0(IntroScreen::onTouchItem, this, 4));
//	addChild(item, 1);
//	item->setPositionX(s.width / 2);
////	item->setPositionY(posY - 550);
//    item->setPositionY(posY - 700);
//	item->runIn(4);
//	item->setTag(14);
//    
//    item = IntroItem::create();
//    item->setValue(cfg->getValue("rate",Value("Settings")).asString(), CC_CALLBACK_0(IntroScreen::onTouchItem, this, 5));
//    addChild(item, 1);
//    item->setPositionX(s.width / 2);
////    item->setPositionY(posY - 700);
//    item->setPositionY(posY - 850);
//    item->runIn(5);
//    item->setTag(15);
}

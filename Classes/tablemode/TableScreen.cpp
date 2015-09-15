//
//  TableScreen.cpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/15/15.
//
//

#include "TableScreen.h"
#include "../base/Util.h"
#include "../Constants.h"

TableScreen::TableScreen()
{
    auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_TABLE);
    Size s = util::graphic::getScreenSize();
    bg->setPosition(s.width / 2, s.height / 2);
    addChild(bg, 1);
    bg->setTag(1);
    
    Vector<FiniteTimeAction*> vec;
    vec.pushBack(DelayTime::create(0.3f));
    vec.pushBack(CallFunc::create(CC_CALLBACK_0(TableScreen::animateIn, this)));
    runAction(Sequence::create(vec));
    
    util::common::stopAllSounds(true);
}

void TableScreen::animateIn()
{
    
}
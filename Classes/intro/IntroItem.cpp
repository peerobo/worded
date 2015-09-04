//
//  IntroItem.cpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/3/15.
//
//

#include "IntroItem.h"
#include "../Constants.h"
#include "../base/Util.h"

void IntroItem::setValue(std::string label, std::function<void()> callback)
{
    Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL,label);
    lbl->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    lbl->setScale(0.8f);
    addChild(lbl);
    lbl->setTag(10);
    Size s = lbl->getContentSize();
    this->setContentSize(Size(s.width*0.8f,s.height*0.8f));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _cback = callback;

}

void IntroItem::runIn(int delay)
{
    auto node = getChildByTag(10);
    
    node->setOpacity(0);
    Vector<FiniteTimeAction*> v;
    if(delay > 0)
        v.pushBack(DelayTime::create(delay*0.2f));
    v.pushBack(FadeIn::create(0.6f));
    node->runAction(Sequence::create(v));
    node->setPositionY(-100);
    node->runAction(MoveBy::create(0.6f+delay*0.2f, Vec2(0,100)));
}

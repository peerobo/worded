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

bool IntroItem::onTouchBegan(cocos2d::Touch *t, cocos2d::Event *e)
{
    if(util::graphic::checkHit(t, e->getCurrentTarget()))
    {
        return true;
    }
    return false;
}

void IntroItem::fadeOut()
{
    auto node = getChildByTag(10);
    node->runAction(FadeOut::create(0.7f));
}

void IntroItem::blink()
{
    auto node = getChildByTag(10);
	util::effects::blink(node);
}

void IntroItem::onTouchEnded(cocos2d::Touch *t, cocos2d::Event *e)
{
    if(_cback)
        _cback();
}

void IntroItem::runOut(int delay)
{
    Size s = util::graphic::getScreenSize();
    Vector<FiniteTimeAction*> v;
    if(delay > 0)
        v.pushBack(DelayTime::create(delay*0.2f));
    v.pushBack(MoveBy::create(0.7f, Vec2(-s.width,0)));
    v.pushBack(RemoveSelf::create());
    this->runAction(Sequence::create(v));
    
    auto node = getChildByTag(10);
    node->runAction(FadeOut::create(0.4f+delay*0.2f));
}

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
    
    EventListenerTouchOneByOne* evt = EventListenerTouchOneByOne::create();
    evt->onTouchBegan = CC_CALLBACK_2(IntroItem::onTouchBegan, this);
    evt->onTouchEnded = CC_CALLBACK_2(IntroItem::onTouchEnded, this);
    evt->setSwallowTouches(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evt, this);
}

void IntroItem::runIn(int delay)
{
    auto node = getChildByTag(10);
	util::effects::reveal(node, delay);
}
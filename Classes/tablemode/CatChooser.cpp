/*
 * CatChooser.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: hachan
 */

#include "CatChooser.h"
#include "../base/Util.h"
#include "../Constants.h"
#include "../base/comp/FScrollList.h"
#include "../WordedApp.h"
#include "TableScreen.h"
#include "TableLogic.h"

CatChooser::CatChooser():LAYER_GUI(2), LAYER_LBL(3)
{
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_TABLE);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 1);
	bg->setTag(1);

	Vector<FiniteTimeAction*> vec;
	vec.pushBack(DelayTime::create(0.3f));
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(CatChooser::animateIn, this)));
	runAction(Sequence::create(vec));

}

bool CatChooser::catTouchBegan(cocos2d::Touch* t, cocos2d::Event* e)
{
    if(util::graphic::checkHit(t, e->getCurrentTarget()))
    {
        return true;
    }
    return false;
}

void CatChooser::catTouchEnd(cocos2d::Touch* t, cocos2d::Event* e, std::string cat)
{
    if(util::graphic::checkTouchStill(t))
    {
        util::graphic::loadTexAtl(cat, false);
        WordedApp::loadSound(cat);
        // list
        Node* child = getChildByTag(2);
        util::effects::disappear(child);
        // lbl
        child =getChildByTag(3);
        // change scene
        util::effects::fadeAndRemove(child, 1.f, std::bind(&util::graphic::changeSceneWithLayer,TableScreen::create()));
        // init logic
        (new TableLogic())->init(cat);
        util::common::playSound(Constants::ASS_SND_CLICK, false);
    }
}

Node* CatChooser::createCatItem(const std::string &cat, int type)
{
    auto container = Node::create();
    
    auto bg = util::graphic::getSprite(StringUtils::format("%s%d",Constants::ASS_ICO_CAT_BG,type));
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    Size itemSize = bg->getContentSize();
    bg->setPosition(0, 120);
    container->addChild(bg,0);
    
    auto catIcon = util::graphic::getSprite(StringUtils::format("%s%s", Constants::ASS_ICO_PREFIX,cat.c_str()));
    catIcon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    catIcon->setPosition(itemSize.width/2, itemSize.height/2 + bg->getPositionY());
    container->addChild(catIcon,0);
    
    auto lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, cat);
    lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    lbl->setPosition(itemSize.width/2, 0);
    lbl->setScale(0.7f);
    container->addChild(lbl,1);
    
    itemSize.height += bg->getPositionY();
    container->setContentSize(itemSize);
    
    std::string catClone = cat;
    EventListenerTouchOneByOne* evt = EventListenerTouchOneByOne::create();
    evt->onTouchBegan = CC_CALLBACK_2(CatChooser::catTouchBegan,this);
    evt->onTouchEnded = CC_CALLBACK_2(CatChooser::catTouchEnd,this, catClone);
    container->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evt, container);
    return container;
}

void CatChooser::animateIn()
{
	Size s = util::graphic::getScreenSize();

	Configuration* cfg = Configuration::getInstance();

    std::vector<std::string> v = WordedApp::getAllCats();
    Node* catNode = createCatItem(v[0],0);
	Size catSize = catNode->getContentSize();
	Size listSize((catSize.width + 50)*2, (catSize.height+50)*2);
	FScrollList* scList = FScrollList::create();
	scList->initView(listSize, 50,0.03f, FScrollList::SCROLL_TYPE::HORIZONTAL, 2, -1, true);
    int count = 0;
    for (std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); it++) {
        count = count%4;
        scList->addAutoPosItem( createCatItem((*it), count));
        count++;
    }
    scList->setPosition(s.width/2,s.height/2);
    scList->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(scList,LAYER_GUI);
    scList->setTag(2);
    util::effects::reveal(scList);
    
    Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL,cfg->getValue("categories").asString());
    lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    addChild(lbl,LAYER_LBL);
    lbl->setPosition(s.width/2,s.height - 150);
    util::effects::reveal(lbl);
    lbl->setTag(3);
}

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
#include "../gui/ScoreGUI.h"
#include "../IntroScreen.h"
#include "../base/ScoreDB.h"
#include "../base/comp/PageIndicator.h"

CatChooser::CatChooser():LAYER_GUI(2), LAYER_LBL(3)
{
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_TABLE);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 1);
	bg->setTag(199);

	Vector<FiniteTimeAction*> vec;
	vec.pushBack(DelayTime::create(0.3f));
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(CatChooser::animateIn, this)));
	runAction(Sequence::create(vec));
	scheduleUpdate();
}

void CatChooser::update(float dt)
{
	auto list = dynamic_cast<FScrollList*>(getChildByTag(2));
	auto pages = dynamic_cast<PageIndicator*>(getChildByTag(4));
	if (list && pages)
	{
		pages->curPage = list->getCurrentPage();
		pages->totalPage = list->getTotalPage();
	}
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
	int star = ScoreDB::instance->getScoreFor(STAR_KEY_FOR(cat.c_str()));
	
    auto bg = util::graphic::getSprite(StringUtils::format("%s%d",Constants::ASS_ICO_CAT_BG,type));
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    Size itemSize = bg->getContentSize();
    bg->setPosition(0, 120);	
    container->addChild(bg,0);
    
    auto catIcon = util::graphic::getSprite(StringUtils::format("%s%s", Constants::ASS_ICO_PREFIX,cat.c_str()));
    catIcon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    catIcon->setPosition(itemSize.width/2, itemSize.height/2 + bg->getPositionY());
    container->addChild(catIcon,0);
    
	std::string catClone = Configuration::getInstance()->getValue(StringUtils::format("c_%s", cat.c_str()),Value(cat)).asString();	
	util::common::capitalize(catClone);
    auto lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, catClone);
    lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    lbl->setPosition(itemSize.width/2, 0);
    lbl->setScale(0.7f);
    container->addChild(lbl,1);

	// check finish
    if(star == WordedApp::STAR_MAX)
	{
		auto icon = util::graphic::getSprite(Constants::ASS_ICO_CHECK);
		icon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		Rect r = lbl->getBoundingBox();
		icon->setPosition(r.getMaxX() + 20, r.getMinY());
		container->addChild(icon, 0);
	}

    itemSize.height += bg->getPositionY();
    container->setContentSize(itemSize);
    
	catClone = cat;
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
    scList->setPosition(s.width/2,s.height/2 - 50);
    scList->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(scList,LAYER_GUI);
    scList->setTag(2);
    util::effects::reveal(scList);
    
	int star = ScoreDB::instance->getScoreFor(WordedApp::STARTOTAL_KEY);
	auto starCount = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, StringUtils::toString(star));
	starCount->setTag(20);
	starCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	starCount->setPosition(s.width / 2 - 10, s.height - 310);
	starCount->setScale(0.8f);
	addChild(starCount, LAYER_LBL);
	util::effects::reveal(starCount);

	auto icon = util::graphic::getSprite(Constants::ASS_ICO_STAR);
	icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	icon->setPosition(s.width / 2 + 30, s.height - 300);
	addChild(icon, LAYER_GUI);	
	util::effects::reveal(icon);

    Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL,cfg->getValue("categories").asString());
    lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    addChild(lbl,LAYER_LBL);
    lbl->setPosition(s.width/2,s.height - 70);
    util::effects::reveal(lbl);
    lbl->setTag(3);

	auto backBt = ui::Button::create();
	addChild(backBt, 1);
	backBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_BACK), ui::Widget::TextureResType::PLIST);
	backBt->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	backBt->setPosition(Vec2(100, s.height - 100));
	util::graphic::addClickBtCallback(backBt, CC_CALLBACK_0(CatChooser::onBackScreen,this));


	/*util::common::stopAllSounds();
	Node* n = ScoreGUI::create("Adjectives1", 90, 99, 5, []() {}, []() {});
	addChild(n,LAYER_LBL);*/

	auto pageIndicator = PageIndicator::create(Constants::ASS_ICO_CURR_PAGE, Constants::ASS_ICO_PAGE);
	pageIndicator->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	pageIndicator->setPosition(s.width/2, 150);
	pageIndicator->setTag(4);
	addChild(pageIndicator, 1);
}

void _internalChangeScene()
{
	util::graphic::changeSceneWithLayer(IntroScreen::create());
}

void CatChooser::onBackScreen()
{
	auto v = getChildren();
	int vsize = v.size();
	for (auto c : v)
	{
		int tag = c->getTag();
		if(tag == 199)
			util::effects::fadeAndRemove(c, 1, std::bind(&_internalChangeScene));
		else if(tag!=2)
			util::effects::fadeAndRemove(c, 0.5f);
	}
	auto list = dynamic_cast<FScrollList*>( getChildByTag(2));
	list->clearAllItems();
	list->removeFromParent();

	// cache next bg
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_INTRO);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 0);

	util::common::playSound(Constants::ASS_SND_CLICK, false);
}
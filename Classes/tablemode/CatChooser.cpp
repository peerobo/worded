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
#include "../gui/MultiBtDlg.h"
#include "../GlobalVar.h"
#include "../gui/AlertGUI.h"

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

void CatChooser::unlockCat(const std::string& cat, UNLOCK type)
{
	auto v = WordedApp::getAllCats();
	size_t sizeV = v.size();
	int idx = -1;
	for (size_t i = 0; i < sizeV; i++)
	{
		if (v[i] == cat)
		{
			idx = i;
			break;
		}
	}
	if (type == UNLOCK::RATE)
	{
		util::common::saveValue(WordedApp::KEY_RATE_IDX, Value(idx));
		time_t t = time(NULL);
		double tD = t;
		util::common::saveValue(WordedApp::KEY_RATE_START_TIME, Value(tD));
		WordedApp::setRateCatIdx(idx);
	}
	else if (type == UNLOCK::AD)
	{
		util::common::saveValue(WordedApp::KEY_AD_IDX, Value(idx));
		time_t t = time(NULL);
		double tD = t;
		util::common::saveValue(WordedApp::KEY_AD_START_TIME, Value(tD));
		WordedApp::setAdCatIdx(idx);
	}
	else
	{
		int star = ScoreDB::instance->getScoreFor(WordedApp::STARTOTAL_KEY);
		if (star >= WordedApp::STAR_MAX)
		{
			int count = util::common::getValue(WordedApp::KEY_NUM_CAT_UNLOCKED).asInt();
			if (count == idx)
			{
				count++;
				util::common::saveValue(WordedApp::KEY_NUM_CAT_UNLOCKED, Value(count));
				WordedApp::setUnlockCatNum(count);
			}
			else
			{
				auto gui = AlertGUI::create();
				std::string msg = Configuration::getInstance()->getValue("prevNotUnlocked").asString();
				auto catClone = Configuration::getInstance()->getValue(StringUtils::format("c_%s", cat.c_str()), Value(cat)).asString();
				util::common::capitalize(catClone);
				util::common::replace(msg, "@cat", catClone);
				gui->setMsg(msg);
				gui->show();
			}
		}
		else
		{
			auto alert = AlertGUI::create();
			std::string msg = Configuration::getInstance()->getValue("notEnoughStars").asString();
			util::common::replace(msg,"@star", StringUtils::toString(WordedApp::STAR_MAX));
			util::common::replace(msg, "@pt", StringUtils::toString(WordedApp::STAR_MIN_PT));
			alert->setMsg(msg);
			alert->show();
		}
	}
	auto scene = dynamic_cast<CatChooser*>(GlobalVar::curScene);
	if (scene)
	{		
		auto list = dynamic_cast<FScrollList*>(scene->getChildByTag(2));
		if (!list)
			return;
		auto vc = list->getAllItems();
		if (idx > -1)
		{
			if (vc.size()> idx && vc.at(idx))
			{
				vc.at(idx)->removeChildByTag(12);
			}
		}
	}
}

void CatChooser::onUnlockByRate(int btIdx, const std::string& cat, Node* node)
{
	// advance next dialog or unlock
	if (btIdx == 0)
	{
		util::platform::rate();
		Vector<FiniteTimeAction*> vAct;
		vAct.pushBack(DelayTime::create(15));
		vAct.pushBack(CallFunc::create(CC_CALLBACK_0(CatChooser::unlockCat,this,cat,UNLOCK::RATE)));
		this->runAction(Sequence::create( vAct));
		node->removeFromParent();
	}
	else
	{
		auto multiBtDlg = MultiBtDlg::create();
		auto cfg = Configuration::getInstance();
		std::string title = "";
		std::string msg = "";
		std::vector<std::string> v;
		title = Configuration::getInstance()->getValue(StringUtils::format("c_%s", cat.c_str()), Value(cat)).asString();
		util::common::capitalize(title);
		msg = cfg->getValue("normalUnlock").asString();
		v = { cfg->getValue("watchAd").asString(),
			cfg->getValue("useStars").asString(),
			cfg->getValue("buyFreeAd").asString() };
		multiBtDlg->setData(title, msg, v);
		multiBtDlg->show();
	}
}

void CatChooser::pause(bool isPause)
{
	if (isPause)
		util::common::stopMusic(true);
	else
		util::common::playMusic(Constants::ASS_SND_THEME);

}

void CatChooser::vungleReward(bool isReward, const std::string& cat)
{
	if (isReward)
	{
		unlockCat(cat, UNLOCK::AD);
	}
	else
	{
		auto alert = AlertGUI::create();
		alert->setMsg(Configuration::getInstance()->getValue("videoSkip").asString());
		alert->show();
	}
}

void CatChooser::onUnlockNormal(int btIdx, const std::string& cat, Node* node)
{
	if (btIdx != -1)
	{
		Configuration* cfg = Configuration::getInstance();
		node->removeFromParent();
		if (btIdx == 0) // watch ad
		{
			if (!util::ad::isVideoAdAvailable())
			{
				auto alert = AlertGUI::create();
				alert->setMsg(cfg->getValue( "videoAdFailed").asString());
				alert->show();
			}
			else
			{
				util::ad::showVungle(CC_CALLBACK_1(CatChooser::pause,this),CC_CALLBACK_1(CatChooser::vungleReward,this,cat));
			}
		}
		else if(btIdx == 1) // use stars
		{
			
		}
		else
		{

		}
	}
}

void CatChooser::catTouchEnd(cocos2d::Touch* t, cocos2d::Event* e, std::string cat)
{
    if(util::graphic::checkTouchStill(t))
    {
		auto container = e->getCurrentTarget();
		if(container->getChildByTag(12))
		{
			auto lockedBG = container->getChildByTag(13);
			if (!lockedBG->isVisible())
			{
				lockedBG->setVisible(true);
			}
			else
			{
				bool checkShowRateDlg = WordedApp::checkShowRateDlg();
				auto multiBtDlg = MultiBtDlg::create();
				auto cfg = Configuration::getInstance();
				std::string title = "";
				std::string msg = "";
				std::vector<std::string> v; 
				if (checkShowRateDlg)
				{
					title = Configuration::getInstance()->getValue(StringUtils::format("c_%s", cat.c_str()), Value(cat)).asString();
					util::common::capitalize(title);
					msg = cfg->getValue("rateAppUnlock").asString();
					v = { cfg->getValue("rate").asString()};
					multiBtDlg->onBtClickCB = CC_CALLBACK_1(CatChooser::onUnlockByRate,this, cat, multiBtDlg);
				}
				else
				{
					title = Configuration::getInstance()->getValue(StringUtils::format("c_%s", cat.c_str()), Value(cat)).asString();
					util::common::capitalize(title);
					msg = cfg->getValue("normalUnlock").asString();
					v = { cfg->getValue("watchAd").asString(), 
						cfg->getValue("useStars").asString(), 
						cfg->getValue("buyFreeAd").asString() };
				}
				multiBtDlg->setData( title, msg, v);
				multiBtDlg->show();

				lockedBG->setVisible(false);
			}
			
		}
		else
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
}

Node* CatChooser::createCatItem(const std::string &cat, int type, bool isLocked)
{
    auto container = Node::create();
	int star = ScoreDB::instance->getScoreFor(STAR_KEY_FOR(cat.c_str()));
	auto cfg = Configuration::getInstance();
	
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
	
	if (isLocked)
	{
		catClone = cat;
		auto lockedIcon = util::graphic::getSprite(Constants::ASS_ICO_LOCK);
		lockedIcon->setPosition(Vec2(itemSize.width, bg->getPositionY()));
		lockedIcon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		container->addChild(lockedIcon, 0);
		lockedIcon->setTag(12);
		
		auto lockedBG = util::graphic::getSprite(Constants::ASS_ICO_BG_CAT_LOCK);
		lockedBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		lockedBG->setPosition(itemSize.width/2, itemSize.height/2 + bg->getPositionY());
		container->addChild(lockedBG, 0);
		lockedBG->setTag(13);
		lockedBG->setVisible(false);
		auto lblDesc = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, cfg->getValue("try").asString());
		lblDesc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
		lblDesc->setPosition(itemSize.width/2, itemSize.height - 50);
		lockedBG->addChild(lblDesc);
		lblDesc->setColor(Constants::COLOR_LIGHT_BLUE);
		lblDesc = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, cfg->getValue("unlock").asString());
		lblDesc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		lblDesc->setPosition(itemSize.width/2, bg->getPositionY());
		lockedBG->addChild(lblDesc);		
		lblDesc->setColor(Constants::COLOR_LIGHT_BLUE);
	}

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
	int unlocked = WordedApp::getUnlockedCat();
    std::vector<std::string> v = WordedApp::getAllCats();
    Node* catNode = createCatItem(v[0],0, false);
	int adCatIdx = WordedApp::getAdCat();
	int rateCatIdx = WordedApp::getRateCat();
	Size catSize = catNode->getContentSize();
	Size listSize((catSize.width + 50)*2, (catSize.height+50)*2);
	FScrollList* scList = FScrollList::create();
	scList->initView(listSize, 50,0.03f, FScrollList::SCROLL_TYPE::HORIZONTAL, 2, -1, true);
    int count = 0;
	int i = 0;
    for (std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); it++) {
        count = count%4;
        scList->addAutoPosItem( createCatItem((*it), count, !(i < unlocked || i == adCatIdx || i==rateCatIdx)));
        count++;
		i++;
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

    Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_SHADOW,cfg->getValue("categories").asString());
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
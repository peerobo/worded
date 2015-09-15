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

CatChooser::CatChooser():LAYER_GUI(2), LAYER_LBL(3), LAYER_CAT(4)
{
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_TABLE);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 1);
	bg->setTag(1);

	std::vector<int> v({ LAYER_GUI,LAYER_LBL,LAYER_CAT });
	util::graphic::generateLayerWithTag(this, v, 2);

	Vector<FiniteTimeAction*> vec;
	vec.pushBack(DelayTime::create(0.3f));
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(CatChooser::animateIn, this)));
	runAction(Sequence::create(vec));
}


void CatChooser::animateIn()
{
	Size s = util::graphic::getScreenSize();

	Configuration* cfg = Configuration::getInstance();
	Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL,cfg->getValue("categories").asString());
	lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	addChild(lbl,LAYER_LBL);
	lbl->setPosition(s.width/2,s.height - 150);
	util::effects::reveal(lbl);

	Sprite* catNode = util::graphic::getSprite(StringUtils::format("%s%d",Constants::ASS_ICO_CAT_BG,0));
	Size catSize = catNode->getContentSize();
	Size listSize(s.width -100, s.height - 400);
	FScrollList* scList = FScrollList::create();
	scList->initView(listSize, listSize.width- catSize.width*2,0.1f,FScrollList::SCROLL_TYPE::HORIZONTAL,2,2);
}

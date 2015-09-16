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
#include "TableLogic.h"
#include "../GlobalVar.h"

TableScreen::~TableScreen()
{
	score = NULL;
	timeBar = NULL;
	word = NULL;
	TableLogic* gl = static_cast<TableLogic*>( GlobalVar::gameLogic);
	if(gl)
	{
		gl->kill();
		CC_SAFE_DELETE(gl);
	}
}

TableScreen::TableScreen():ICON_LAYER(4),LABEL_LAYER(3),GUI_LAYER(2), TAG_BG_ICON(100), TAG_ICON(100)
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
    
    score = NULL;
    timeBar = NULL;
    word = NULL;

    std::vector<int> layers = {GUI_LAYER, ICON_LAYER, LABEL_LAYER};
    util::graphic::generateLayerWithTag(this,layers, 1);
}

void TableScreen::animateIn()
{
	util::common::stopAllSounds(true);
	Size s = util::graphic::getScreenSize();
	float sw = s.width /8;

    score = Label::createWithBMFont(Constants::ASS_FNT_NORMAL,"0");
    score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    score->setPosition(sw/2,s.height-150);
    getChildByTag(LABEL_LAYER)->addChild(score);
    util::effects::reveal(score,0.3f);

    timeBar = util::graphic::getSprite(Constants::ASS_ICO_BAR_TABLE);
    timeBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    timeBar->setPosition(sw*7/2,s.height-150);
    getChildByTag(GUI_LAYER)->addChild(timeBar);
    util::effects::reveal(timeBar);

    std::string wordStr = "";
    util::common::capitalize(wordStr);
    word = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, wordStr);
    word->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    word->setPosition(s.width/2, s.height - 500);
    getChildByTag(LABEL_LAYER)->addChild(word);
    word->setOpacity(0);

    makeTiles();
}

void TableScreen::makeTiles(std::vector<std::string> v)
{
	Node* layer = getChildByTag(GUI_LAYER);
	bool needInit = true;
	for (int i = 0; i < 9; ++i) {
		if(layer->getChildByTag(TAG_BG_ICON + i))
		{
			needInit = false;
			break;
		}
	}
	if(needInit)
	{
		for (int i = 0; i < 9; ++i) {

		}
	}
}

void TableScreen::vanishTile(int idx)
{

}

void TableScreen::vanishTiles()
{

}

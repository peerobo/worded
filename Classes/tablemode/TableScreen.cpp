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
#include "../WordedApp.h"

TableScreen::~TableScreen()
{
	score = NULL;
	timeBar = NULL;
	word = NULL;
    TableLogic* gl = static_cast<TableLogic*>( GlobalVar::gameLogic);
    util::graphic::removeTexAtl(gl->word);
	if(gl)
	{
		gl->kill();
		CC_SAFE_DELETE(gl);
	}
}

bool TableScreen::onTouchWordTileBegan(cocos2d::Touch *t, cocos2d::Event *e)
{
    if (util::graphic::checkHit(t, e->getCurrentTarget())) {
        auto gl = static_cast<TableLogic*>( GlobalVar::gameLogic);
        bool check = gl->isPause || !gl->isPlaying || gl->isShowScore || (gl->pauseTime > 0);
        if (check) {
            return false;
        }
        return true;
    }
    return false;
}

void TableScreen::onTouchWordTileEnded(cocos2d::Touch *t, cocos2d::Event *e)
{
    auto bt = e->getCurrentTarget();
    std::string word = bt->getName();
    auto gl = static_cast<TableLogic*>( GlobalVar::gameLogic);
    if (!WordedApp::validateAnswer(gl->word, word)) {
        vanishTile(bt->getTag()-TAG_BG_ICON);
    }
    gl->answerWord = word;
}

void TableScreen::update(float dt)
{
    TableLogic* gl = static_cast<TableLogic*>(GlobalVar::gameLogic);
    // update bar
    timeBar->setScaleX(gl->currTime/gl->totalTime);
    score->setString(StringUtils::toString(gl->score));
    if(gl->isShowScore) // finish category
    {
        vanishTiles();
        gl->isShowScore = false;
        Node* n = WordedApp::getScoreBoard(gl->cat, gl->score, gl->score, CC_CALLBACK_0(TableScreen::onBack2Cats, this), CC_CALLBACK_0(TableScreen::onRetry, this));
        getChildByTag(GUI_LAYER)->addChild(n);
        n->setVisible(false);
        currWord = "";
        log("show result");
    }
    else if(gl->isPlaying) // game is playing
    {
        std::string logicWord = gl->word;
        if(currWord!=logicWord)
        {
            currWord = logicWord;
            Vector<FiniteTimeAction*> v;
            v.pushBack(FadeOut::create(0.2f));
            v.pushBack(CallFunc::create(CC_CALLBACK_0(Label::setString,word,logicWord)));
            v.pushBack(FadeIn::create(0.4f));
            word->runAction(Sequence::create(v));
            
            makeTiles(gl->formation);
        }
        
        
    }
    else    // is Pause
    {
        
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
    currWord = "";
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
    timeBar->setPosition(sw + sw*7/2,s.height-150);
    getChildByTag(GUI_LAYER)->addChild(timeBar);
    util::effects::reveal(timeBar);

    std::string wordStr = "";
    util::common::capitalize(wordStr);
    word = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, wordStr);
    word->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    word->setPosition(s.width/2, s.height - 400);
    getChildByTag(LABEL_LAYER)->addChild(word);
    word->setOpacity(0);

    tilesRect = Rect(70, 150, s.width-140, s.height - 650);

    makeTiles();
    
    TableLogic* gl = static_cast<TableLogic*>(GlobalVar::gameLogic);
    Vector<FiniteTimeAction*> v;
    v.pushBack(DelayTime::create(2.f));
    v.pushBack(CallFunc::create(CC_CALLBACK_0(TableLogic::start,gl)));
    this->runAction(Sequence::create(v));
    
    scheduleUpdate();
}

void TableScreen::onRetry()
{
    
}

void TableScreen::onBack2Cats()
{
    
}

void TableScreen::makeTiles(std::vector<std::string> v)
{
	Node* layer = getChildByTag(GUI_LAYER);
	Node* icons = getChildByTag(ICON_LAYER);
	bool needInit = true;
	for (int i = 0; i < 9; ++i) {
		if(layer->getChildByTag(TAG_BG_ICON + i))
		{
			needInit = false;
			break;
		}
	}
	Size eachTile(tilesRect.size.width/3,tilesRect.size.height/3);
	size_t wordSize = v.size();

	for (int i = 0; i < 9; ++i)
	{
		if(needInit) // both layers are emptied
		{
			// add bg;
            Node* bg = util::graphic::getSprite(StringUtils::format("%s%d",Constants::ASS_ICO_BG_TABLE,i));
			int row = 2-(i/3);
			int col = i%3;
			bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			layer->addChild(bg);
			bg->setPositionX(tilesRect.getMinX()+ eachTile.width*(col+0.5f));
			bg->setPositionY(tilesRect.getMinY()+ eachTile.height*(row+0.5f));
			util::effects::reveal(bg, 0.15f*i);
			bg->setTag(TAG_BG_ICON+i);
            
            EventListenerTouchOneByOne* evt = EventListenerTouchOneByOne::create();
            evt->onTouchBegan = CC_CALLBACK_2(TableScreen::onTouchWordTileBegan,this);
            evt->onTouchEnded = CC_CALLBACK_2(TableScreen::onTouchWordTileEnded, this);
            evt->setSwallowTouches(true);
            bg->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evt, bg);
            
			// add icon
			if(i < wordSize)
			{
				bg->setName(v[i]);
				Node* icon = util::graphic::getSprite(v[i]);
				icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				icons->addChild(icon);
				icon->setPosition(bg->getPosition());
				util::effects::reveal(icon, 0.15f*i);
				icon->setTag(TAG_ICON+i);
			}
		}
		else
		{
			Vector<FiniteTimeAction*> vAct;
			// get existing bg
			Node* bg = layer->getChildByTag(TAG_BG_ICON+i);
			if(bg)
			{
				float time = 0.15f*i;
				if(time > 0)
					vAct.pushBack(DelayTime::create(time));
				vAct.pushBack(ScaleTo::create(0.2f,0.01f));
				vAct.pushBack(ScaleTo::create(0.4f,1.f));
				// add child icon
				Node* oldIcon = icons->getChildByTag(TAG_ICON+i);
				Vector<FiniteTimeAction*> vOld;
				if(oldIcon)
				{
					if(time > 0)
						vOld.pushBack(DelayTime::create(time));
					vOld.pushBack(ScaleTo::create(0.2f,0.01f));
					vOld.pushBack(RemoveSelf::create());
				}
				// new icon
				bg->setName(v[i]);
				Node* icon = util::graphic::getSprite(v[i]);
				icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				icons->addChild(icon);
				icon->setPosition(bg->getPosition());
				icon->setScale(0.01f);
				icon->setOpacity(0);
				icon->setTag(TAG_ICON+i);
				Vector<FiniteTimeAction*> iconActs;
				iconActs.pushBack(DelayTime::create(time+0.2f));
				iconActs.pushBack(Spawn::createWithTwoActions(
						FadeIn::create(0.4f),
						ScaleTo::create(0.4f,1.f)
						));

				if(oldIcon)
					oldIcon->runAction(Sequence::create(vOld));
				icon->runAction(Sequence::create(iconActs));
				bg->runAction(Sequence::create(vAct));
			}
		}
	}

}

void TableScreen::vanishTile(int idx)
{
	Node* layer = getChildByTag(GUI_LAYER);
	Node* icons = getChildByTag(ICON_LAYER);

	auto bg = layer->getChildByTag(TAG_BG_ICON +idx);
	bg->runAction(ScaleTo::create(0.4f,0.01f));

	auto icon = icons->getChildByTag(TAG_ICON + idx);
	icon->runAction(ScaleTo::create(0.4f,0.01f));

	// add pause timeout
    auto gl =static_cast<TableLogic*>(GlobalVar::gameLogic);
    gl->pauseTime = 0.5f;
}

void TableScreen::vanishTiles()
{
	Node* layer = getChildByTag(GUI_LAYER);
	Node* icons = getChildByTag(ICON_LAYER);
	for (int i = 0; i < 9; ++i)
	{
		Vector<FiniteTimeAction*> vAct;
		Vector<FiniteTimeAction*> vIconAct;
		Node* bg = layer->getChildByTag(TAG_BG_ICON+i);
		if(bg)
		{
			vAct.pushBack(ScaleTo::create(0.2f,0.01f));
			vAct.pushBack(RemoveSelf::create());
			bg->runAction(Sequence::create(vAct));

			Node* icon = icons->getChildByTag(TAG_ICON+i);
			if(icon)
			{
				vIconAct.pushBack(ScaleTo::create(0.2f,0.01f));
				vIconAct.pushBack(RemoveSelf::create());
				icon->runAction(Sequence::create(vIconAct));
			}

		}
	}
}

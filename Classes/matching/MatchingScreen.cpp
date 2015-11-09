#include "MatchingScreen.h"
#include "MatchingLogic.h"
#include "../GlobalVar.h"
#include "../base/Util.h"
#include "../WordedApp.h"
#include "../Constants.h"
#include "../base/ScoreDB.h"
#include "../gui/ScoreGUI.h"
#include "../IntroScreen.h"

MatchingScreen::~MatchingScreen()
{	
	if(GlobalVar::gameLogic)
	{
		auto gl = static_cast<MatchingLogic*>(GlobalVar::gameLogic);				
		if (gl)
		{
			gl->kill();
			CC_SAFE_DELETE(gl);
		}
	}	
}

void MatchingScreen::enableTouch()
{
	log("enable touch");
	disableTouch = false;
}

MatchingScreen::MatchingScreen()
{
	disableTouch = false;
	playingWordSoundID = UINT32_MAX;
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_MATCHING);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 1);
	bg->setTag(1);

	Vector<FiniteTimeAction*> vec;
	vec.pushBack(DelayTime::create(0.1f));
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(MatchingScreen::animateIn, this)));
	runAction(Sequence::create(vec));

	float ratio = s.width > s.height ? s.width / s.height : s.height / s.width;
	extendedScreen = ratio > 1.5f;	
}

void MatchingScreen::animateIn()
{
	util::common::stopMusic(true);
	MatchingLogic* gl = static_cast<MatchingLogic*>(GlobalVar::gameLogic);
	Vector<FiniteTimeAction*> v;
	v.pushBack(DelayTime::create(1.0f));
	v.pushBack(CallFunc::create(CC_CALLBACK_0(MatchingLogic::start, gl)));
	this->runAction(Sequence::create(v));
	Size s = util::graphic::getScreenSize();
	
	auto timeBar = util::graphic::getSprite(Constants::ASS_ICO_BAR_TABLE);
	timeBar->setTag(TAG_TIMER_BAR);
	timeBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	timeBar->setPosition(s.width / 2, s.height);
	timeBar->setScale(s.width / timeBar->getContentSize().width);
	this->addChild(timeBar, LAYER_ICON);
	timeBar->setOpacity(0);

	auto scoreLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, "0");
	scoreLbl->setTag(TAG_SCORE_LBL);
	scoreLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	scoreLbl->setScale(0.8f);
	this->addChild(scoreLbl, LAYER_LABEL);
	scoreLbl->setOpacity(0);	

	// check if need to show category label
	if (extendedScreen)
	{
		auto catLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, "");
		catLbl->setTag(TAG_CAT_LBL);
		catLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(catLbl, LAYER_LABEL);
		catLbl->setPosition(s.width / 2, s.height - 100);
		catLbl->setOpacity(0);
		scoreLbl->setPosition(s.width/2 , s.height - 240);
	}
	else
	{
		scoreLbl->setPosition(s.width/2 , s.height - 80);
	}

	scheduleUpdate();
}

void MatchingScreen::onTouchWord(int idx)
{
	MatchingLogic* gl = static_cast<MatchingLogic*>(GlobalVar::gameLogic);
	if (gl->pauseTime > 0 || disableTouch)
		return;	
	if (idx == firstWordIdx) // select the same tile
		return;
	const float TIME_DELAY = 0.8f;
	if (playingWordSoundID != UINT32_MAX)
	{
		util::common::stopSound(playingWordSoundID);
	}
	std::string word = gl->formation[idx];
	util::common::replace(word, "+", "");
	playingWordSoundID = util::common::playSound((word + Constants::ASS_SUFFIX_SOUND).c_str(), false);
	
	if (firstWordIdx != -1)
	{
		secondWordIdx = idx;
		gl->secWord = word;
		disableTouch = true;
		log("disable touch 2nd word");
		if (gl->firstWord == gl->secWord) // vanish tile
		{
			auto bg = getChildByTag(TAG_BG_WORD_PREFIX + secondWordIdx);
			auto icon = getChildByTag(TAG_ICON_WORD_PREFIX + secondWordIdx);
			float scale = bg->getScale();
			util::effects::zoomTo(bg, -1, scale, scale*1.1f);
			scale = icon->getScale();
			std::function<void()> later = CC_CALLBACK_0(MatchingScreen::resetAllTiles, this);
			if (gl->remainingWord == 2)
			{
				later = CC_CALLBACK_0(MatchingScreen::enableTouch, this);
			}
			else
			{
				// enable touch
				auto v = Vector<FiniteTimeAction*>();
				v.pushBack(DelayTime::create(TIME_DELAY));
				v.pushBack(CallFunc::create( CC_CALLBACK_0(MatchingScreen::enableTouch, this)));
				runAction(Sequence::create(v));
			}

			util::effects::zoomTo(
				icon, 
				-1, 
				scale, 
				scale/0.9f * 1.1f, 
				std::bind(
					static_cast<void (MatchingScreen::*)( int, int, std::function<void()>)>(&MatchingScreen::vanishTile),
					this,
					firstWordIdx,
					secondWordIdx, 
					later
				)
			);
		}
		else
		{
			// restore remain
			auto bg = getChildByTag(TAG_BG_WORD_PREFIX + secondWordIdx);
			auto icon = getChildByTag(TAG_ICON_WORD_PREFIX + secondWordIdx);
			float scale = bg->getScale();
			util::effects::zoomTo(bg, -1, scale, scale*1.1f);
			scale = icon->getScale();
			std::function<void()> later = CC_CALLBACK_0(MatchingScreen::resetAllTiles, this);
			util::effects::zoomTo(
				icon,
				-1,
				scale,
				scale * 1.1f,
				later);
			// enable touch
			auto v = Vector<FiniteTimeAction*>();
			v.pushBack(DelayTime::create(TIME_DELAY));
			v.pushBack(CallFunc::create(CC_CALLBACK_0(MatchingScreen::enableTouch, this)));
			runAction(Sequence::create(v));
		}
	}
	else
	{
		firstWordIdx = idx;
		gl->firstWord = word;
		disableTouch = true;
		log("disable touch 1st word");
		bool addCB = false;
		for (size_t i = 0; i < 10; i++)
		{
			float scale;
			auto bg = getChildByTag(TAG_BG_WORD_PREFIX + i);
			auto icon = getChildByTag(TAG_ICON_WORD_PREFIX + i);
			if (i == firstWordIdx)
			{
				scale = bg->getScale();
				util::effects::zoomTo(bg, -1, scale, scale * 1.1f);
				scale = icon->getScale();				
				if (!addCB)
				{
					util::effects::zoomTo(icon, -1, scale, scale * 1.1f, CC_CALLBACK_0(MatchingScreen::enableTouch,this));
					addCB = true;
				}
				else
				{
					util::effects::zoomTo(icon, -1, scale, scale * 1.1f);
				}
				continue;
			}
			if (bg)
			{
				scale = bg->getScale();
				util::effects::zoomTo(bg, -1, scale, scale * 0.9f);
				scale = icon->getScale();
				
				if (!addCB)
				{
					util::effects::zoomTo(icon, -1, scale, scale * 0.9f, CC_CALLBACK_0(MatchingScreen::enableTouch,this));
					addCB = true;
				}
				else
				{
					util::effects::zoomTo(icon, -1, scale, scale * 0.9f);
				}
			}
		}

	}
}

void MatchingScreen::onBack2Intro()
{
	util::graphic::changeSceneWithLayer(IntroScreen::create());
	util::common::playMusic(Constants::ASS_SND_THEME);
	util::common::playSound(Constants::ASS_SND_CLICK, false);
}

void MatchingScreen::onRetry()
{
	
	// remove score
	getChildByTag(23)->removeFromParent();

	MatchingLogic* gl = static_cast<MatchingLogic*>(GlobalVar::gameLogic);
	Vector<FiniteTimeAction*> v;
	v.pushBack(DelayTime::create(1.5f));
	v.pushBack(CallFunc::create(CC_CALLBACK_0(MatchingLogic::start, gl)));
	this->runAction(Sequence::create(v));
	util::common::playSound(Constants::ASS_SND_CLICK, false);
}

void MatchingScreen::update(float dt)
{
	MatchingLogic* gl = static_cast<MatchingLogic*>(GlobalVar::gameLogic);
	Size s = util::graphic::getScreenSize();
	auto timerBar = getChildByTag(TAG_TIMER_BAR);
	auto scoreLbl = dynamic_cast<Label*>( getChildByTag(TAG_SCORE_LBL));
	Label* catLbl = NULL;
	if (extendedScreen)
		catLbl = dynamic_cast<Label*>(getChildByTag(TAG_CAT_LBL));
	// update bar
	timerBar->setScaleX(gl->currTime / gl->totalTime *(s.width / timerBar->getContentSize().width));
	scoreLbl->setString(StringUtils::toString(gl->score));
	if (gl->isShowScore) // finish game
	{		
		util::common::stopAllSounds();
		vanishTiles();
		gl->isShowScore = false;
		int best = ScoreDB::instance->getScoreFor(WordedApp::SCORE_MATCHING);
		int coin = ScoreDB::instance->getScoreFor(WordedApp::COIN_KEY);
		Node* n = ScoreGUI::create(coin, gl->score, best, CC_CALLBACK_0(MatchingScreen::onBack2Intro, this), CC_CALLBACK_0(MatchingScreen::onRetry, this));
		n->setTag(23);
		addChild(n, LAYER_ICON);
		// save score
		bool isSave = false;
		if (gl->score > best)
		{
			ScoreDB::instance->setScoreFor(WordedApp::SCORE_MATCHING,gl->score);
			isSave = true;
			util::platform::setScoreGC(WordedApp::getGCKey("worded_matching"), gl->score);
		}
		if (isSave)
			ScoreDB::instance->saveDB();		
		util::graphic::removeTexAtl(curCat);
		WordedApp::unloadSound(curCat);
		curCat = "";
		firstWordIdx = -1;
		secondWordIdx = -1;
		timerBar->setVisible(false);
		scoreLbl->setVisible(false);
		if (catLbl)
			catLbl->setVisible(false);
	}
	else if (gl->isPlaying) // game is playing
	{
		timerBar->setVisible(true);
		scoreLbl->setVisible(true);
		if (catLbl)
		{
			catLbl->setVisible(true);			
		}
		std::string currCat = gl->getCurrCat();
		if (currCat != curCat) // new cat -> start new round
		{
			if (catLbl)
			{
				std::string title = Configuration::getInstance()->getValue("scoreCat").asString();
				std::string catTitle = Configuration::getInstance()->getValue(StringUtils::format("c_%s", currCat.c_str()), Value(currCat)).asString();
				util::common::capitalize(catTitle);
				util::common::replace(title, "@cat", catTitle);
				catLbl->setString(title);
			}
			// remove old cat
			if (curCat != "")
			{
				WordedApp::unloadSound(curCat);
				util::graphic::removeTexAtl(curCat);
			}
			
			// load new cat
			WordedApp::loadSound(currCat);
			util::graphic::loadTexAtl(currCat, false);

			Vector<FiniteTimeAction*> v;
			v.pushBack(DelayTime::create(1.f));
			v.pushBack(CallFunc::create(CC_CALLBACK_0(MatchingScreen::startRound, this)));
			this->runAction(Sequence::create(v));			
			playingWordSoundID = UINT32_MAX;
			curCat = currCat;
			util::effects::reveal(timerBar);
			util::effects::reveal(scoreLbl);
			if (catLbl)
				util::effects::reveal(catLbl);
		}
		// alert player about time is running out
		if (gl->currTime <= 3 && !playedTimeout) 
		{
			util::common::playSound(Constants::ASS_SND_TIMEOUT, false);
			playedTimeout = true;
		}
		else if (gl->currTime > 3)
		{
			playedTimeout = false;
		}
	}
	else    // is Pause
	{
		
	}
}

void MatchingScreen::startRound()
{			
	firstWordIdx = secondWordIdx = -1;	
	util::common::stopAllSounds();
	auto gl = static_cast<MatchingLogic*>(GlobalVar::gameLogic);
	Size s = util::graphic::getScreenSize();
	auto v = gl->formation;
	bool needHidBG = false;
	if (gl->getCurrCat() == "colors" || gl->getCurrCat() == "positions")
		needHidBG = true;
	Vec2 pos;
	const float interval = 0.125f;
	float segment = s.width / 3;
	for (size_t i = 0; i < 10; i++)
	{
		std::string word = v[i];
		bool isWord = util::common::replace(word, "+", "");
		// create bg
		Node* bg = util::graphic::getSprite(StringUtils::format("%s%d", Constants::ASS_ICO_BG_TABLE, i));
		bg->setVisible(!needHidBG);
		addChild(bg, LAYER_GUI);
		bg->setTag(TAG_BG_WORD_PREFIX + i);
		bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		util::effects::zoomTo(bg, interval*i);
		
		// add touch
		util::graphic::addNodeClickCallback(bg, CC_CALLBACK_0(MatchingScreen::onTouchWord, this, i));
		// create icon or word
		Node* iconOrWord = NULL;
		Size bgSize(360, 360);
		if (isWord)
		{
			util::common::capitalize(word);
			Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_SHADOW, word);
			lbl->setScale(0.75f);
			lbl->setMaxLineWidth(bgSize.width / 0.95f);
			lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			lbl->setAlignment(TextHAlignment::CENTER);			
			addChild(lbl, LAYER_LABEL);
			iconOrWord = lbl;
			util::effects::zoomTo(lbl, interval*i, 0, 0.75f);
		}
		else
		{
			iconOrWord = util::graphic::getSprite(word);
			iconOrWord->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			addChild(iconOrWord, LAYER_ICON);
			util::effects::zoomTo(iconOrWord, interval*i, 0, util::graphic::fit(bgSize, iconOrWord));
		}
		iconOrWord->setTag(TAG_ICON_WORD_PREFIX + i);
		// set position
		if (i < 9)
		{
			int mod = i % 3;
			switch (mod)
			{
			case 0:
				pos.x = segment / 2;
				pos.y = segment * (i / 3 + 1);
				break;
			case 1:
				pos.x = segment *1.5f;
				pos.y = (i / 3 + 0.5f)*segment;
				break;
			default:
				pos.x = segment*2.5f;
				pos.y = segment*(i / 3 + 1);
				break;
			}
		}
		else
		{
			pos.x = segment*1.5f;
			pos.y = segment*3.5f;
		}
		bg->setPosition(pos);
		iconOrWord->setPosition(pos);
	}
}

void MatchingScreen::vanishTiles()
{
	for (size_t i = 0; i < 10; i++)
	{
		auto n = getChildByTag(TAG_BG_WORD_PREFIX + i);
		if (n)
			util::effects::fadeAndRemove(n);
		n = getChildByTag(TAG_ICON_WORD_PREFIX + i);
		if (n)
			util::effects::fadeAndRemove(n);		
	}	
}

void MatchingScreen::vanishTile(int idx1, int idx2, std::function<void()> cb)
{
	float TIME = 0.25f;
	auto n = getChildByTag(TAG_BG_WORD_PREFIX + idx1);
	if(n)
		util::effects::fadeAndRemove(n, TIME);
	n = getChildByTag(TAG_ICON_WORD_PREFIX + idx1);
	if(n)
		util::effects::fadeAndRemove(n, TIME);
	
	n = getChildByTag(TAG_BG_WORD_PREFIX + idx2);
	if (n)
		util::effects::fadeAndRemove(n, TIME);
	n = getChildByTag(TAG_ICON_WORD_PREFIX + idx2);
	if (n)
		util::effects::fadeAndRemove(n, TIME, cb);
}

void MatchingScreen::resetAllTiles()
{	
	for (size_t i = 0; i < 10; i++)
	{
		float scale;
		auto bg = getChildByTag(TAG_BG_WORD_PREFIX + i);
		auto icon = getChildByTag(TAG_ICON_WORD_PREFIX + i);
		if (bg)
		{			
			scale = bg->getScale();
			util::effects::zoomTo(bg, -1, scale, scale / (i == firstWordIdx || i== secondWordIdx ? 1.1f : 0.9f));
			scale = icon->getScale();
			
			util::effects::zoomTo(icon, -1, scale, scale / (i == firstWordIdx || i == secondWordIdx ? 1.1f : 0.9f));
			
			
		}
	}
	
	firstWordIdx = secondWordIdx = -1;	
}

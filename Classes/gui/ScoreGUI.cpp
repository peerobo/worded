#include "ScoreGUI.h"
#include "../WordedApp.h"
#include "../base/Util.h"
#include "../Constants.h"
#include <ui/UILayout.h>
#include <string>
#include "AlertGUI.h"
#include "../base/ScoreDB.h"
#include "../GlobalVar.h"

void ScoreGUI::share(CONST_STR img, CONST_STR msg, bool fb)
{
	util::common::playSound(Constants::ASS_SND_CLICK,false);
	bool ret;
	if (fb)
	{
		ret = util::platform::share2FB(img, msg);
	}
	else
	{
		ret = util::platform::share2Twitter(img, msg);
	}
	if (!ret)
	{
		auto alert = AlertGUI::create();
		auto cfg = Configuration::getInstance();
		alert->setMsg( cfg->getValue(fb ? "socialErrorFB" : "socialErrorTwitter").asString());
		alert->show();
	}
	else
	{
		getChildByTag(45)->removeFromParent();
	}
}

ScoreGUI::ScoreGUI(int coin, int score, int bestScore, std::function<void()> backCB, std::function<void()> retryCB): ScoreGUI(coin, "", score, bestScore, -1, backCB, retryCB)
{
	
}

void ScoreGUI::showShareBts(bool ret, const std::string & str)
{
	if (ret)
	{
		auto cfg = Configuration::getInstance();
		Size s = util::graphic::getScreenSize();
		auto pos = Vec2(s.width / 2, 340);
		auto bg = util::graphic::getSprite(Constants::ASS_ICO_BG_BUBBLE);
		bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		bg->setPosition(pos);
		util::graphic::addClosedWhenClickOutside(bg);
		this->addChild(bg, 3);

		std::string msgShare = cfg->getValue("shareMsg").asString();
		util::common::replace(msgShare, "@pt", StringUtils::toString(targetScore));
		util::common::replace(msgShare, "@cat", cat);
		util::common::replace(msgShare, "@url", Constants::KEY_APPID);

		auto size = bg->getContentSize();
		auto bt = ui::Button::create();
		bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_FB), ui::Widget::TextureResType::PLIST);
		bt->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		bt->setPosition(Vec2(size.width/4,size.height/2));
		bg->addChild(bt);
		util::graphic::addClickBtCallback(bt, CC_CALLBACK_0(ScoreGUI::share, this, str, msgShare, true));

		bt = ui::Button::create();
		bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_TWITTER), ui::Widget::TextureResType::PLIST);
		bt->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		bt->setPosition(Vec2(size.width * 3 / 4, size.height / 2));
		bg->addChild(bt);
		util::graphic::addClickBtCallback(bt, CC_CALLBACK_0(ScoreGUI::share, this, str, msgShare, false));

		bg->setTag(45);
	}
	else
	{
		Configuration* cfg = Configuration::getInstance();
		auto msgBox = AlertGUI::create();
		msgBox->setMsg(cfg->getValue("imageError").asString());
		msgBox->show();
	}
}

void ScoreGUI::saveImage()
{
	util::common::playSound(Constants::ASS_SND_CLICK, false);
	util::graphic::captureScreen(CC_CALLBACK_2(ScoreGUI::showShareBts,this));
}

ScoreGUI::ScoreGUI(int coin, std::string cat, int score, int bestScore, int star, std::function<void()> backCB, std::function<void()> retryCB)
{
	Configuration* cfg = Configuration::getInstance();
	this->cat = cfg->getValue(StringUtils::format("c_%s",cat.c_str()),Value(cat)).asString();
	util::common::capitalize(this->cat);
	this->star = star;
	this->bestScore = bestScore;
	Size s = util::graphic::getScreenSize();	

	std::string title = "";
	if (cat != "")
	{
		title = cfg->getValue("scoreCat").asString();		
		std::string catTitle = Configuration::getInstance()->getValue(StringUtils::format("c_%s", cat.c_str()), Value(cat)).asString();
		util::common::capitalize(catTitle);
		util::common::replace(title, "@cat", catTitle);		
	}
	else
	{
		title = cfg->getValue("puzzlemode").asString();
	}
	Label* catLbl = Label::createWithBMFont(Constants::ASS_FNT_SHADOW, title);
	catLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	catLbl->setPosition(s.width / 2, s.height - 200);
	util::effects::reveal(catLbl);
	addChild(catLbl, 1);

	if (star > -1)
	{
		auto starCount = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, StringUtils::format("%d/%d", star, WordedApp::STAR_MAX));
		starCount->setTag(20);
		starCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		starCount->setPosition(s.width / 2 + 30, s.height - 380);
		starCount->setScale(0.8f);
		addChild(starCount, 1);
		util::effects::reveal(starCount);

		auto icon = util::graphic::getSprite(Constants::ASS_ICO_STAR);
		icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		icon->setPosition(s.width / 2 - 30, s.height - 360);
		addChild(icon, 3);
		icon->setTag(19);
		util::effects::reveal(icon);
	}

	Label* descLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, cfg->getValue("scoreDesc").asString());
	descLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	descLbl->setPosition(s.width / 2, s.height - 520);
	descLbl->setScale(0.8f);
	util::effects::reveal(descLbl);
	addChild(descLbl, 1);

	scoreProgress = 0;
	Label* scoreLbl = Label::createWithBMFont(Constants::ASS_FNT_BIG, "100");
	scoreLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	scoreLbl->setPosition(s.width / 2, s.height / 2);
	util::effects::reveal(scoreLbl, 0.4f);
	addChild(scoreLbl, 2);
	scoreLbl->setTag(23);
	Rect rect = scoreLbl->getBoundingBox();
	scoreLbl->setString("0");

	Label* ptLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, "pt");
	ptLbl->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	ptLbl->setPosition(rect.getMaxX(), rect.getMinY() + rect.size.height / 2);
	util::effects::reveal(ptLbl, 0.4f);
	ptLbl->setScale(0.8f);
	ptLbl->setTag(24);
	addChild(ptLbl, 1);
	
	if (star > -1)
	{

		Sprite* icoStarBG = util::graphic::getSprite(Constants::ASS_ICO_STAR);
		icoStarBG->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		icoStarBG->setPosition(Vec2(rect.getMaxX(), rect.getMaxY()));
		icoStarBG->setColor(Color3B::BLACK);
		icoStarBG->setVisible(false);
		icoStarBG->setTag(21);
		addChild(icoStarBG, 3);

		Sprite* icoStar = util::graphic::getSprite(Constants::ASS_ICO_STAR);
		icoStar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		icoStar->setTag(12);
		ui::Layout* mask = ui::Layout::create();
		mask->setClippingEnabled(true);
		Size iconSize = icoStar->getContentSize();
		mask->setPosition(Vec2(rect.getMaxX(), rect.getMaxY()));
		mask->setContentSize(iconSize);
		mask->addChild(icoStar);
		mask->setTag(22);
		mask->setVisible(false);
		addChild(mask, 3);
		mask->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}

	std::string best;
	if (score > bestScore)
	{
		best = cfg->getValue("newBestScore").asString();
	}
	else
	{
		best = cfg->getValue("bestScore").asString();
		util::common::replace(best, "@number", StringUtils::toString(bestScore));
	}

	Label* highScoreLabel = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, best);
	highScoreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	highScoreLabel->setPosition(rect.getMidX(), rect.getMinY() - 100);
	addChild(highScoreLabel, 1);
	highScoreLabel->setScale(0.8f);
    highScoreLabel->setOpacity(0);
    highScoreLabel->setTag(25);
    if(score == 0)
        util::effects::reveal(highScoreLabel, 0.4f);
	highScoreLabel->setColor(Color3B(248, 143, 116));

	auto backBt = ui::Button::create();
	addChild(backBt, 3);
	backBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_BACK), ui::Widget::TextureResType::PLIST);
	backBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	backBt->setPosition(Vec2(s.width / 2 - 300, 100));
	util::graphic::addClickBtCallback(backBt, backCB);

	auto shareBt = ui::Button::create();
	addChild(shareBt, 3);
	shareBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_SHARE), ui::Widget::TextureResType::PLIST);
	shareBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	shareBt->setPosition(Vec2(s.width / 2, 100));
	util::graphic::addClickBtCallback(shareBt, std::bind(&ScoreGUI::saveImage, this));

	auto retryBt = ui::Button::create();
	addChild(retryBt, 3);
	retryBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_RETRY), ui::Widget::TextureResType::PLIST);
	retryBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	retryBt->setPosition(Vec2(s.width / 2 + 300, 100));
	util::graphic::addClickBtCallback(retryBt, retryCB);

	targetScore = score;
	scheduleUpdate();
	updateFlag = 0;
#ifdef LITE
	time_t currTime = time(NULL);
	if (currTime - GlobalVar::timeShowAd >= Constants::TIME_SHOW_AD * 60)
	{
		GlobalVar::timeShowAd = currTime;
		enableTouch = false;
	}
	else
	{
		enableTouch = true;
	}
#else
	enableTouch = true;
#endif
		
	Node* node = Node::create();
	node->setContentSize(s);
	EventListenerTouchOneByOne* evt = EventListenerTouchOneByOne::create();
	evt->onTouchBegan = CC_CALLBACK_2(ScoreGUI::swallowTouchHelper, this);
	evt->setSwallowTouches(true);
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evt, node);
	addChild(node, 10);
}

bool ScoreGUI::swallowTouchHelper(Touch* t, Event* e)
{
	if (!enableTouch)
		return true;
	else
		return false;
}

void ScoreGUI::update(float dt)
{
	Node::update(dt);
	if (scoreProgress == 0)
	{
		Label* lbl = dynamic_cast<Label*>(getChildByTag(23));
		if (lbl->getOpacity() == 255)
		{
			lbl->setString(StringUtils::toString(scoreProgress));
			Rect rect = lbl->getBoundingBox();
			Node* lblPt = getChildByTag(24);
			lblPt->setPositionX(rect.getMaxX() + 20);
		}
	}
	if (scoreProgress != targetScore)
	{
		updateFlag += dt;
		
		if (updateFlag > 0.1f)
		{
			updateFlag = 0;
			Label* lbl = dynamic_cast<Label*>(getChildByTag(23));
			if (lbl->getOpacity() == 255)
			{
				auto starIcon = getChildByTag(22);
				Node* starBG;
				float percent;
				Rect rect = lbl->getBoundingBox();
				Node* lblPt = getChildByTag(24);
				lblPt->setPositionX(rect.getMaxX() + 20);
				if (starIcon)
				{
					if (scoreProgress == 0)
					{
						starIcon->setVisible(true);
						auto starBG = getChildByTag(21);
						starBG->setVisible(true);
						util::common::playSound(Constants::ASS_SND_INCREASE, false);
					}
					starBG = getChildByTag(21);				
					starIcon->setPositionX(lblPt->getPositionX());
					starBG->setPositionX(lblPt->getPositionX());
					percent = scoreProgress / (float)WordedApp::STAR_MIN_PT;
					percent = percent > 1 ? 1 : percent;
					Size starSize = starIcon->getChildByTag(12)->getContentSize();
					starSize.height = percent * starSize.height;
					starIcon->setContentSize(starSize);
					starBG->setOpacity(255 * percent);
					starIcon->getChildByTag(12)->setOpacity(255 * percent);
				}
				
				int dScore = (targetScore - scoreProgress);
				scoreProgress += dScore<3 ? dScore : dScore / 3;
				lbl->setString(StringUtils::toString(scoreProgress));

				if (scoreProgress == targetScore)
				{
                    util::common::stopAllSounds();
                    // highscore label
                    util::effects::reveal(getChildByTag(25));
                    
					if (starIcon)
					{
						if (targetScore >= WordedApp::STAR_MIN_PT)  // finish effect
						{
							// check stars achievement
							{
								int starTotal = ScoreDB::instance->getScoreFor(std::string(WordedApp::STARTOTAL_KEY));
								std::vector<std::string> starsAch = {
									std::string(WordedApp::ACH_1_STAR),
									std::string(WordedApp::ACH_25_STAR),
									std::string(WordedApp::ACH_50_STAR),
									std::string(WordedApp::ACH_100_STAR),
									std::string(WordedApp::ACH_145_STAR)
								};
								float starsNum[] = { 1,25,50,100,145 };
								int len = starsAch.size();
								for (int i = 0; i< len; i++) {
									bool checkAch = util::common::getValue(starsAch[i]).asBool();
									if (!checkAch)
									{
										float percent = starTotal / starsNum[i];
										if (((int)percent) * 100 >= 100)
										{
											// update and save
											util::platform::updateAchGC(
												WordedApp::getGCKey(starsAch[i].c_str()),
												100,
												std::bind(&util::common::saveValue, starsAch[i], Value(true))
												);
										}
										else
										{
											util::platform::updateAchGC(starsAch[i], percent * 100);
										}
										break;
									}
								}
							}

							// check 90 points achievement
							{
								int time90 = ScoreDB::instance->getScoreFor(std::string(WordedApp::TOTAL_90STAR));
								std::vector<std::string> _90achs = {
									std::string(WordedApp::ACH_ONE_90),
									std::string(WordedApp::ACH_FIVE_90),
									std::string(WordedApp::ACH_TEN_90),
									std::string(WordedApp::ACH_ALL_90)
								};
								float num90[] = { 1,5,10,29 };
								int lenPt = _90achs.size();

								for (int i = 0; i< lenPt; i++) {
									bool checkAch = util::common::getValue(_90achs[i]).asBool();
									if (!checkAch)
									{
										float percent = time90 / num90[i];
										if (((int)percent) * 100 >= 100)
										{
											// update and save
											util::platform::updateAchGC(
												WordedApp::getGCKey(_90achs[i].c_str()),
												100,
												std::bind(&util::common::saveValue, _90achs[i], Value(true))
												);
										}
										else
										{
											util::platform::updateAchGC(WordedApp::getGCKey(_90achs[i].c_str()), percent * 100);
										}
										break;
									}
								}
							}


							if (star < WordedApp::STAR_MAX)
							{
								auto targetStar = getChildByTag(19);
								auto starLbl = dynamic_cast<Label*>(getChildByTag(20));

								Size starS = starBG->getContentSize();
								starBG->setVisible(false);
								Vector<FiniteTimeAction*> v;
								// star fly effect
								Vec2 pos = targetStar->getPosition();
								pos.x -= starS.width / 2;
								pos.y -= starS.height / 2;
								auto ccCfg = ccBezierConfig();
								ccCfg.endPosition = pos;
								Vec2 currPos = starIcon->getPosition();
								ccCfg.controlPoint_1 = Vec2(currPos.x + 70, currPos.y + 70);
								ccCfg.controlPoint_2 = Vec2(pos.x + 120, pos.y - 40);
								v.pushBack(BezierTo::create(0.7f, ccCfg));
								v.pushBack(CallFunc::create(CC_CALLBACK_0(Label::setString, starLbl, StringUtils::format("%d/%d", (star + 1), WordedApp::STAR_MAX))));
								v.pushBack(RemoveSelf::create());
								starIcon->getChildByTag(12)->runAction(FadeOut::create(0.7f));
								starIcon->runAction(Sequence::create(v));
								util::common::playSoundNoResponse(Constants::ASS_SND_HIGHSCORE, false);
								// update achievement
								if (star + 1 == WordedApp::STAR_MAX)
								{
									bool checkAch = util::common::getValue(WordedApp::ACH_1_CAT).asBool();
									if (!checkAch)
									{
										util::platform::updateAchGC(WordedApp::getGCKey(WordedApp::ACH_1_CAT), 100, std::bind(&util::common::saveValue, WordedApp::ACH_1_CAT, Value(true)));
									}
								}
							}

						}
						else if (percent >= 0.7f)    // show star suggest
						{
							auto starSuggest = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, StringUtils::format("(%d/%dpt)", targetScore, WordedApp::STAR_MIN_PT));
							starSuggest->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							starSuggest->setScale(0.7f);
							starSuggest->setPosition(starIcon->getPosition());
							starSuggest->setOpacity(0);
							auto suggestV = Vector<FiniteTimeAction*>();
							suggestV.pushBack(DelayTime::create(0.7f));
							suggestV.pushBack(FadeIn::create(0.7f));
							starBG->runAction(FadeOut::create(0.7f));
							starIcon->getChildByTag(12)->runAction(FadeOut::create(0.7f));
							addChild(starSuggest, 1);
							starSuggest->runAction(Sequence::create(suggestV));

						}
					}
					
					
					if (targetScore > bestScore)
					{
						Size s = util::graphic::getScreenSize();
						Sprite* highScore = util::graphic::getSprite(Constants::ASS_ICO_HIGHSCORE);
						highScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
						highScore->setPosition(s.width / 2, s.height / 2);
						highScore->setVisible(false);
						highScore->setScale(3);
						addChild(highScore, 3);
						Vector<FiniteTimeAction*> vAct;
						vAct.pushBack(DelayTime::create(1.5f));
						vAct.pushBack(Show::create());
						vAct.pushBack(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.3f));						
						highScore->runAction(Sequence::create(vAct));
						Vector<FiniteTimeAction*> vSound;
						vSound.pushBack(DelayTime::create(1.7f));
						vSound.pushBack(CallFunc::create(std::bind(&util::common::playSoundNoResponse, Constants::ASS_SND_ENDGAME, false)));
						highScore->runAction(Sequence::create( vSound));
					}
                    
#ifdef LITE
					if (!enableTouch)	// show ad
					{
						util::ad::showLeadboltAd();
						enableTouch = true;
					}
#endif
				}
			}
		}		
	}	
}
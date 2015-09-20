#include "ScoreGUI.h"
#include "../WordedApp.h"
#include "../base/Util.h"
#include "../Constants.h"
#include <ui/UILayout.h>
#include <string>

ScoreGUI::ScoreGUI(std::string cat, int score, int bestScore, int star, std::function<void()> backCB, std::function<void()> retryCB)
{
	this->star = star;
	this->bestScore = bestScore;
	Size s = util::graphic::getScreenSize();	
	Configuration* cfg = Configuration::getInstance();

	std::string title = cfg->getValue("scoreCat").asString();
	std::string catTitle = cat;
	util::common::capitalize(catTitle);
	util::common::replace(title, "@cat", catTitle);
	Label* catLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, title);
	catLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	catLbl->setPosition(s.width / 2, s.height - 200);
	util::effects::reveal(catLbl);
	addChild(catLbl, 1);

	auto starCount = Label::createWithBMFont(Constants::ASS_FNT_NORMAL,StringUtils::format("%d/%d", star, WordedApp::STAR_MAX));
	starCount->setTag(20);
	starCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	starCount->setPosition(s.width / 2 + 30, s.height - 380);
	starCount->setScale(0.8f);
	addChild(starCount,1);
	util::effects::reveal(starCount);

	auto icon = util::graphic::getSprite(Constants::ASS_ICO_STAR);
	icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	icon->setPosition(s.width / 2 - 30, s.height - 360);
	addChild(icon, 3);
	icon->setTag(19);
	util::effects::reveal(icon);

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
	util::effects::reveal(highScoreLabel, 0.4f);
	highScoreLabel->setColor(Color3B(229, 94, 72));	

	auto backBt = ui::Button::create();
	addChild(backBt, 3);
	backBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_BACK), ui::Widget::TextureResType::PLIST);
	backBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	backBt->setPosition(Vec2(s.width / 2 - 200, 100));
	util::graphic::addClickBtCallback(backBt, backCB);

	auto shareBt = ui::Button::create();
	addChild(shareBt, 3);
	shareBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_SHARE), ui::Widget::TextureResType::PLIST);
	shareBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	shareBt->setPosition(Vec2(s.width / 2, 100));
	util::graphic::addClickBtCallback(shareBt, std::bind(&util::graphic::captureScreen));

	auto retryBt = ui::Button::create();
	addChild(retryBt, 3);
	retryBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_RETRY), ui::Widget::TextureResType::PLIST);
	retryBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	retryBt->setPosition(Vec2(s.width / 2 + 200, 100));
	util::graphic::addClickBtCallback(retryBt, retryCB);

	targetScore = score;

	scheduleUpdate();
	updateFlag = 0;
}

void ScoreGUI::update(float dt)
{
	Node::update(dt);
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
				if (scoreProgress == 0)
				{
					starIcon->setVisible(true);

					auto starBG = getChildByTag(21);
					starBG->setVisible(true);
				}
				
				int dScore = (targetScore - scoreProgress);
				scoreProgress += dScore<3 ? dScore : dScore / 3;
				lbl->setString(StringUtils::toString(scoreProgress));

				Rect rect = lbl->getBoundingBox();
				Node* lblPt = getChildByTag(24);
				lblPt->setPositionX(rect.getMaxX());

				Size starSize = starIcon->getChildByTag(12)->getContentSize();
				starSize.height = scoreProgress / (float)WordedApp::STAR_MIN_PT * starSize.height;
				starIcon->setContentSize(starSize);

				if (scoreProgress == targetScore && targetScore >= WordedApp::STAR_MIN_PT)
				{
					auto targetStar = getChildByTag(19);
					auto starLbl = dynamic_cast<Label*>( getChildByTag(20));
					auto starBG = getChildByTag(21);
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
					v.pushBack(CallFunc::create(CC_CALLBACK_0(Label::setString, starLbl, StringUtils::format("%d/%d", (star +1), WordedApp::STAR_MAX))));
					v.pushBack(RemoveSelf::create());
					starIcon->runAction(Sequence::create(v));
					starIcon->getChildByTag(12)->runAction(FadeOut::create(0.7f));

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
						vAct.pushBack(DelayTime::create(1));
						vAct.pushBack(Show::create());
						vAct.pushBack(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.3f));
						highScore->runAction(Sequence::create(vAct));
					}
				}
			}
		}
	}	
}
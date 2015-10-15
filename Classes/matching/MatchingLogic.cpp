#include "MatchingLogic.h"
#include "../WordedApp.h"
#include "../base/Looper.h"
#include "../GlobalVar.h"
#include "../base/Util.h"

const int MatchingLogic::LOOPER_IDX = 1;

void MatchingLogic::loop(float dt)
{
	if (!isPause && isPlaying)
	{
		if (pauseTime > 0)
		{
			pauseTime -= dt;
		}
		else
		{
			currTime -= dt;
			if (currTime >= 0)
				validateState();
			else
				endGame();
			
		}
	}
}

void MatchingLogic::init()
{
	isPlaying = false;
	isPause = false;
	totalTime = WordedApp::MATCHING_MODE_TIME[WordedApp::difficult];
	currTime = totalTime;

	firstWord = secWord = "";
	catIdx = -1;
	formation = std::vector<std::string>();
	score = 0;
	level = -1;
	pauseTime = -1;
	isShowScore = -1;
	Looper::instance->addLoop(CC_CALLBACK_1(MatchingLogic::loop, this), LOOPER_IDX);
	GlobalVar::gameLogic = this;
}

void MatchingLogic::kill()
{
	Looper::instance->removeLoop(LOOPER_IDX);
	GlobalVar::gameLogic = NULL;
}

void MatchingLogic::start()
{
	isPlaying = true;
	isPause = false;
	score = 0;
	catRnd = WordedApp::getRndCats(WordedApp::getUnlockedCat(), WordedApp::TABLE_MODE_LEVELS[WordedApp::difficult]);
	firstWord = secWord = "";
	nextFormation();
	level = -1;
	isShowScore = false;
	remainingWord = 10;
	catIdx = -1;
}

void MatchingLogic::validateState()
{
	if (secWord != "")
	{
		if (WordedApp::validateAnswer(firstWord, secWord))
		{
			float rate = WordedApp::TABLE_MODE_SCORE_RATIO[WordedApp::difficult];
			score += currTime* rate;
			remainingWord -= 2;			
			if (remainingWord == 0)
				nextFormation();
			firstWord = "";
			secWord = "";
		}
		else
		{
			firstWord = "";
			secWord = "";
		}
	}
}

void MatchingLogic::nextFormation()
{
	int size = catRnd.size();
	catIdx++;
	if (catIdx == size)
	{
		endGame();
		return;
	}
	pauseTime = WordedApp::MATCHING_MODE_TIME_PAUSE_B4_COUNT;
	formation = WordedApp::getRndFormation(catRnd[catIdx], 5);
	auto v = formation;
	int wsize = formation.size();
	int count = wsize;
	for (int i = 0; i < wsize; i++)
	{
		int idx = rand() % (count + 1);
		if (idx == count)
			formation.push_back("+" + v[i]);
		else
			formation.insert(formation.begin() + idx, "+" + v[i]);
		count++;
	}
	currTime = totalTime;
}

std::string MatchingLogic::getCurrCat()
{
	return catRnd[catIdx];
}

void MatchingLogic::endGame()
{
	isPlaying = false;
	isShowScore = true;
	// decrease count rate
	int rateCount = util::common::getValue(WordedApp::KEY_REMIND_RATE).asInt();
	if (rateCount > -1)
		rateCount--;
	util::common::saveValue(WordedApp::KEY_REMIND_RATE, Value(rateCount));
}

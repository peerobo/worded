//
//  TableLogic.cpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/14/15.
//
//

#include "TableLogic.h"
#include "../GlobalVar.h"
#include "../WordedApp.h"
#include "../base/Looper.h"

const int TableLogic::LOOPER_IDX = 0;

void TableLogic::init(const std::string& cat)
{
    isPlaying = false;
    isPause = false;
    totalTime = WordedApp::TABLE_MODE_TIME[ WordedApp::difficult];
    currTime = totalTime;
    
    word = "";
    this->cat = cat;
    formation = std::vector<std::string>();
    score = 0;
    level = -1;
    answerWord = "";
    pauseTime = -1;
    isShowScore = false;
    Looper::instance->addLoop(CC_CALLBACK_1(TableLogic::loop, this), LOOPER_IDX);
    GlobalVar::gameLogic = this;
}

void TableLogic::loop(float dt)
{
	if(!isPause && isPlaying)
	{
		if(pauseTime > 0)
		{
			pauseTime--;
		}
		else
		{
			currTime-=dt;

			if(currTime >=0)
				validateState();
			else
				endGame();
		}
	}
    
}

void TableLogic::kill()
{
    Looper::instance->removeLoop(LOOPER_IDX);
    GlobalVar::gameLogic = NULL;
}

void TableLogic::start()
{
    isPlaying = true;
    isPause = false;
    score = 0;
    nextWord();
    level = -1;
    isShowScore = false;
}

void TableLogic::validateState()
{
    if(answerWord!="")
    {
        if(WordedApp::validateAnswer(word,answerWord))
        {
            score += currTime* WordedApp::TABLE_MODE_SCORE_RATIO[WordedApp::difficult];
            nextWord();
            answerWord = "";
        }
        else
        {
            penalty();
            answerWord = "";
        }
    }
}

void TableLogic::nextWord()
{
	level++;
	if(level > WordedApp::TABLE_MODE_LEVELS[WordedApp::difficult])
	{
		endGame();
		return;
	}
	pauseTime = WordedApp::TABLE_MODE_TIME_PAUSE_B4_COUNT;
	word = WordedApp::getRndItemInCat(cat);
	formation = WordedApp::getRndFormationWith(cat, word, 10);
	answerWord = "";
	currTime = totalTime;
}

void TableLogic::penalty()
{
	currTime += WordedApp::TABLE_MODE_PENALTY[WordedApp::difficult];
}

void TableLogic::endGame()
{
	isPlaying = false;
	isShowScore = true;
}

bool TableLogic::checkFinishCat()
{
	// check if can get a star
	if(score >= 90)
	{
		return true;
	}
	return false;
}

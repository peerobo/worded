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
    Looper::instance->addLoop(CC_CALLBACK_1(TableLogic::loop, this), LOOPER_IDX);
}

void TableLogic::loop(float dt)
{
    
}

void TableLogic::kill()
{
    Looper::instance->removeLoop(LOOPER_IDX);
}

void TableLogic::start()
{
    isPlaying = true;
}

void validateState();
void nextWord();
void penalty();
void endGame();
void checkFinishCat();
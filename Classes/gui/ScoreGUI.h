#pragma once
#include <cocos2d.h>
#include "../base/Util.h"

USING_NS_CC;

class ScoreGUI : public Node
{
private:		
	float updateFlag;
	int targetScore;
	int star;
	int bestScore;
	std::string cat;
	ScoreGUI(int coin, std::string cat, int score, int bestScore, int star, std::function<void()> backCB, std::function<void()> retryCB);
	ScoreGUI(int coin, int score, int bestScore, std::function<void()> backCB, std::function<void()> retryCB);
	void showShareBts(bool ret, const std::string& str);
	void saveImage();
	void share(CONST_STR img, CONST_STR msg, bool fb);
	bool enableTouch;
	bool swallowTouchHelper(Touch* t, Event* e);
public:
	int scoreProgress;
	static ScoreGUI* create(int coin, std::string cat, int score, int bestScore, int star, std::function<void()> backCB, std::function<void()> retryCB)
	{ 
		ScoreGUI *pRet = new(std::nothrow) ScoreGUI(coin,cat,score,bestScore,star,backCB,retryCB); 
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL; 
			return NULL; 
		} 
	}

	static ScoreGUI* create(int coin, int score, int bestScore, std::function<void()> backCB, std::function<void()> retryCB)
	{
		ScoreGUI *pRet = new(std::nothrow) ScoreGUI(coin, score, bestScore, backCB, retryCB);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	void update(float dt) override;
};

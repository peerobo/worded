#pragma once
#include <cocos2d.h>

USING_NS_CC;

class ScoreGUI : public Node
{
private:	
	float updateFlag;
	int targetScore;
	int star;
	int bestScore;
	ScoreGUI(std::string cat, int score, int bestScore, int star, std::function<void()> backCB, std::function<void()> retryCB);
public:
	int scoreProgress;
	static ScoreGUI* create(std::string cat, int score, int bestScore, int star, std::function<void()> backCB, std::function<void()> retryCB)
	{ 
		ScoreGUI *pRet = new(std::nothrow) ScoreGUI(cat,score,bestScore,star,backCB,retryCB); 
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

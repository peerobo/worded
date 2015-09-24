#pragma once
#include <cocos2d.h>

USING_NS_CC;

class PageIndicator : public Node
{
private:
	int _curPage;
	int _totalPage;
	std::string curFrame;
	std::string frame;
	PageIndicator(const std::string& currPageFrame, const std::string& pageFrame);
public:
	int curPage;
	int totalPage;
	void update(float dt) override;
	static PageIndicator* create(const std::string& currPageFrame, const std::string& pageFrame)
	{
		PageIndicator *pRet = new(std::nothrow) PageIndicator(currPageFrame, pageFrame);
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
};
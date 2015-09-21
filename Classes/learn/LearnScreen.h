#pragma once
#include <cocos2d.h>
USING_NS_CC;

class LearnScreen : public Layer
{
private:
	const int LAYER_GUI;
	const int LAYER_LBL;
	const int LAYER_CAT;

	void animateIn();
	LearnScreen();
public:
	CREATE_FUNC(LearnScreen);
};
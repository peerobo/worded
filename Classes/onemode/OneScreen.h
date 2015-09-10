#pragma once
#include <cocos2d.h>
USING_NS_CC;

class OneScreen : public Layer
{
private:
	const int LAYER_GUI;
	const int LAYER_LBL;
	const int LAYER_CAT;

	void animateIn();
	OneScreen();
public:
	CREATE_FUNC(OneScreen);
};
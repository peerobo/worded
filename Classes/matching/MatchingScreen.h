#pragma once

#include <cocos2d.h>
#include <vector>

USING_NS_CC;

class MatchingScreen : public Layer
{
private:
	const int GUI_LAYER;
	const int LABEL_LAYER;
	const int ICON_LAYER;

	~MatchingScreen();
	MatchingScreen();
	/*void animateIn();
	void makeTiles(std::vector<std::string> tiles = {});
	void vanishTiles();
	void vanishTile(int idx);
	bool onTouchWordTileBegan(Touch* t, Event* e);
	void onTouchWordTileEnded(Touch* t, Event* e);
	void update(float dt) override;
	void onRetry();
	void onBack2Cats();*/
public:
	CREATE_FUNC(MatchingScreen);
};

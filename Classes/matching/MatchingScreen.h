#pragma once

#include <cocos2d.h>
#include <vector>
#include <string>
USING_NS_CC;

class MatchingScreen : public Layer
{
private:
	bool disableTouch;
	std::string curCat;
	bool playedTimeout;
	uint32_t playingWordSoundID;
	int firstWordIdx;
	int secondWordIdx;
	enum CONSTANTS {
		LAYER_MULTIPLY = 100,
		LAYER_ICON = 4,
		LAYER_LABEL = 3,
		LAYER_GUI = 2,
		TAG_BG_WORD_PREFIX = 100,
		TAG_ICON_WORD_PREFIX = 200,
		TAG_TIMER_BAR=70,
		TAG_SCORE_LBL=71,
		TAG_CAT_LBL=72
	};

	~MatchingScreen();
	MatchingScreen();
	bool extendedScreen;
	void animateIn();
	void onTouchWord(int idx);
	/*void makeTiles(std::vector<std::string> tiles = {});	
	bool onTouchWordTileBegan(Touch* t, Event* e);
	void onTouchWordTileEnded(Touch* t, Event* e);	
	void onRetry();
	void onBack2Cats();*/
	void update(float dt) override;
	void startRound();
	void vanishTiles();
	void vanishTile(int idx1, int idx2, std::function<void()> cb = nullptr);
	void resetAllTiles();
	void onBack2Intro();
	void onRetry();
	void enableTouch();
public:
	CREATE_FUNC(MatchingScreen);
};

//
//  TableScreen.hpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/15/15.
//
//

#ifndef TableScreen_hpp
#define TableScreen_hpp

#include <cocos2d.h>
#include <vector>

USING_NS_CC;

class TableScreen : public Layer
{
private:
	const int GUI_LAYER;
	const int LABEL_LAYER;
	const int ICON_LAYER;
	const int TAG_BG_ICON;
	const int TAG_ICON;

	Rect tilesRect;
	Label* score;
	Node* timeBar;
	Label* word;
    std::string currWord;

	~TableScreen();
    TableScreen();
    void animateIn();
    void makeTiles(std::vector<std::string> tiles = {});
    void vanishTiles();
    void vanishTile(int idx);
    bool onTouchWordTileBegan(Touch* t, Event* e);
    void onTouchWordTileEnded(Touch* t, Event* e);
    void update(float dt) override;
    void onRetry();
    void onBack2Cats();
public:
    CREATE_FUNC(TableScreen);
};

#endif /* TableScreen_hpp */

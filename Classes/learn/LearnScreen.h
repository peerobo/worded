#pragma once
#include <cocos2d.h>
#include "../base/Util.h"
#include <vector>
USING_NS_CC;

class LearnScreen : public Layer
{

private:
	std::string cat;
	std::vector<std::string> words;
	int idxWord;
	bool needTut;

	const int LAYER_GUI;
	const int LAYER_LBL;
	const int LAYER_CAT;
	bool isListCat;
	void animateIn();
	void onBackScreen();
	Node* createItem(CONST_STR cat, int type, int w);
	void showWords(CONST_STR cat);
	void showList();
	void setWord();
	void advanceWord(bool next);
	LearnScreen();
public:
	CREATE_FUNC(LearnScreen);
};
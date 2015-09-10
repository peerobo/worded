#pragma once
#include <cocos2d.h>

class WordedApp
{
	static int _unlockedCat;
	static int _currCat;
	static bool _adCat;
	static int _adCatIdx;
public:
	/////////////////////////////////////
	static const int DIFFICULT_EASY;
	static const int DIFFICULT_HARD;
	static const int ONE_MODE_TIME[2];
	static const int ONE_MODE_LEVELS[2];
	static const int TABLE_MODE_TIME[2];
	static const int TABLE_MODE_LEVELS[2];
	/////////////////////////////////////
	static int difficult;
	/////////////////////////////////////
	static void initialize();
	static void rndOneModeCat();
	static int getUnlockedCat();
	static int getAdCat();
	static std::vector<std::string>& getRndFormation(const std::string& cat, int total = 10);
	static std::vector<std::string>& getRndFormationExcept(const std::string& cat, const std::string& exp, int total = 10);
	static std::string& getRndItemInCat(const std::string& cat);
	static bool validateAnswer(const std::string& item1, const std::string& item2);
	static void startOneGame();
	/////////////////////////////////////
	
};

#pragma once
#include <cocos2d.h>
#include <vector>
#include <string>

USING_NS_CC;

#define STAR_KEY_FOR(cat) StringUtils::format("%s%s", WordedApp::STAR_PREFIX_KEY, cat)
#define STAR90_KEY_FOR(cat) StringUtils::format("%s%s", WordedApp::PREFIX_90STAR, cat)

class WordedApp
{
	static int _unlockedCat;
	static int _currCat;
	static int _adCatIdx;
	static int _rateCatIdx;
public:
	/////////////////////////////////////
	static const int DIFFICULT_EASY;
	static const int DIFFICULT_HARD;
	/*static const int ONE_MODE_TIME[2];
	static const int ONE_MODE_LEVELS[2];
    static const int ONE_MODE_PENALTY[2];
    static const float ONE_MODE_SCORE_RATIO[2];*/
	static const int RATE_REMIND_ROUND;
	static const int STAR_MAX;
	static const int STAR_MIN_PT;
	static const int TABLE_MODE_TIME[2];
	static const int TABLE_MODE_LEVELS[2];
    static const int TABLE_MODE_PENALTY[2];
	static const int MATCHING_MODE_TIME[2];
	static const int MATCHING_MODE_PENALTY[2];
	static const float MATCHING_MODE_RATE[2];
	static const int MATCHING_MODE_TIME_PAUSE_B4_COUNT;
	static const int TIME_AD_REMAIN;
	static const int BEGINNER_CAT_NUM;
    static const float TABLE_MODE_SCORE_RATIO[2];
    static const float TABLE_MODE_TIME_PAUSE_B4_COUNT;
	static const char* SCORE_MATCHING;
	static const char* STARTOTAL_KEY;
	static const char* STAR_PREFIX_KEY;
	static const char* COIN_KEY;
    static const char* PREFIX_90STAR;
    static const char* TOTAL_90STAR;
	static const char* KEY_AD_IDX;
	static const char* KEY_RATE_IDX;
	static const char* KEY_AD_START_TIME;
	static const char* KEY_RATE_START_TIME;
	static const char* KEY_REMIND_RATE;
	static const char* KEY_ALREADY_RATE;
	static const char* KEY_NUM_CAT_UNLOCKED;
	static const char* URL_FULL_APP;
    static const char* GC_TOTAL_SCORE;
	// achievement
	static const char* ACH_HARD_MODE;
	static const char* ACH_1_STAR;
	static const char* ACH_25_STAR;
	static const char* ACH_50_STAR;
	static const char* ACH_100_STAR;
	static const char* ACH_145_STAR;
	static const char* ACH_1_CAT;
	static const char* ACH_ONE_90;
	static const char* ACH_FIVE_90;
	static const char* ACH_TEN_90;
	static const char* ACH_ALL_90;
	/////////////////////////////////////
	static int difficult;
	/////////////////////////////////////
	static void initialize();
	static int getUnlockedCat();
	static int getAdCat();
	static int getRateCat();
    static std::vector<std::string> getAllCats();
    static std::vector<std::string> getAllWords(const std::string& cat);
	static std::vector<std::string> getRndFormation(const std::string& cat, int total = 10);
	static std::vector<std::string> getRndFormationExcept(const std::string& cat, const std::string& exc, int total = 10);
	static std::vector<std::string> getRndFormationWith(const std::string& cat, const std::string& with, int total = 10);
	static std::string getRndItemInCat(const std::string& cat);
	static bool validateAnswer(const std::string& item1, const std::string& item2);
	static void playSound(const std::string& word);
	static void loadSound(const std::string& cat);
	static bool checkShowRateDlg();
	static void unloadSound(const std::string& cat);
	static void setRateCatIdx(int catIdx);
	static void setAdCatIdx(int catIdx);
	static void setUnlockCatNum(int num);
    static std::string getGCKey(const char* key);
	static std::vector<std::string> getRndCats(int maxCatIdx, int numCat);
	/////////////////////////////////////
};

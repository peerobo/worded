#include "WordedApp.h"
#include "base/Util.h"
#include <cocos2d.h>
#include "Constants.h"
#include <audio/include/SimpleAudioEngine.h>
#include <ui/UIButton.h>

USING_NS_CC;

const int WordedApp::DIFFICULT_EASY = 0;
const int WordedApp::DIFFICULT_HARD = 1;
const int WordedApp::STAR_MAX = 5;
#ifdef LITE
const int WordedApp::STAR_MIN_PT = 85;
#else
const int WordedApp::STAR_MIN_PT = 82;
#endif
const int WordedApp::TIME_AD_REMAIN = 12;
const int WordedApp::BEGINNER_CAT_NUM = 4;
//const int WordedApp::ONE_MODE_TIME[2] = { 10, 5 };
//const int WordedApp::ONE_MODE_LEVELS[2] = { 10, 10 };
//const int WordedApp::ONE_MODE_PENALTY[2] = {-5,-5};
//const float WordedApp::ONE_MODE_SCORE_RATIO[2] = {0.5f,2.0f};
const int WordedApp::RATE_REMIND_ROUND = 20;
const int WordedApp::TABLE_MODE_TIME[2] = { 15, 8};
const int WordedApp::TABLE_MODE_LEVELS[2] = { 10, 10};
const int WordedApp::TABLE_MODE_PENALTY[2] = {-4,-4};
const float WordedApp::TABLE_MODE_SCORE_RATIO[2] = {1.f/3.f, 1.25f};
const float WordedApp::TABLE_MODE_TIME_PAUSE_B4_COUNT = 1.2f;
const char* WordedApp::STARTOTAL_KEY = "star_total";
const char* WordedApp::STAR_PREFIX_KEY = "star-";
const char* WordedApp::PREFIX_90STAR = "star90-";
const char* WordedApp::TOTAL_90STAR = "star90_total";
const char* WordedApp::ACH_HARD_MODE = "ach_hardmode";
const char* WordedApp::ACH_1_STAR = "ach_1star";
const char* WordedApp::ACH_25_STAR = "ach_25star";
const char* WordedApp::ACH_50_STAR = "ach_50star";
const char* WordedApp::ACH_100_STAR = "ach_100star";
const char* WordedApp::ACH_145_STAR = "ach_145star";
const char* WordedApp::ACH_1_CAT = "ach_1cat";
const char* WordedApp::ACH_ONE_90 = "ach_one90";
const char* WordedApp::ACH_FIVE_90 = "ach_five90";
const char* WordedApp::ACH_TEN_90 = "ach_ten90";
const char* WordedApp::ACH_ALL_90 = "ach_all90";;
const char* WordedApp::GC_TOTAL_SCORE = "totalscore";
const char* WordedApp::KEY_AD_IDX = "key_ad_idx";
const char* WordedApp::KEY_RATE_IDX = "key_rate_idx";
const char* WordedApp::KEY_RATE_START_TIME = "key_rate_start";
const char* WordedApp::KEY_AD_START_TIME = "key_ad_start";
const char* WordedApp::KEY_NUM_CAT_UNLOCKED = "key_unlocked_cat";
const char* WordedApp::KEY_REMIND_RATE = "key_remindRate";
const char* WordedApp::KEY_ALREADY_RATE = "key_rated";
const char* WordedApp::URL_FULL_APP = "https://goo.gl/8V9fhc";
int WordedApp::difficult = WordedApp::DIFFICULT_EASY;

int WordedApp::_currCat = -1;
int WordedApp::_unlockedCat = 4;
int WordedApp::_adCatIdx = -1;
int WordedApp::_rateCatIdx = -1;

void WordedApp::setRateCatIdx(int catIdx)
{
	_rateCatIdx = catIdx;
}

void WordedApp::setUnlockCatNum(int num)
{
	_unlockedCat = num;
}

void WordedApp::setAdCatIdx(int catIdx)
{
	_adCatIdx = catIdx;
}

int WordedApp::getRateCat()
{
	return _rateCatIdx;
}

std::string WordedApp::getRndItemInCat(const std::string& cat)
{
	Configuration* cfg = Configuration::getInstance();
	std::vector<std::string> v = util::common::splitStr(cfg->getValue(cat).asString().c_str(), ';');
	size_t len = v.size();
	return v.at(rand() % len);
}

std::vector<std::string> WordedApp::getAllCats()
{
    Configuration* cfg = Configuration::getInstance();
    ValueVector v = cfg->getValue("cats").asValueVector();
    std::vector<std::string> vs;
    for (ValueVector::iterator it = v.begin(); it != v.end(); it++) {
        vs.push_back(it->asString());
    }
    return  vs;
}

void WordedApp::playSound(const std::string& word)
{
	std::string path = word + std::string( Constants::ASS_SUFFIX_SOUND);
	util::common::playSound(path.c_str(),false);
}

void WordedApp::loadSound(const std::string& cat)
{
	std::vector<std::string> paths = FileUtils::getInstance()->getSearchPaths();
	size_t len = paths.size();
	for(size_t i = 0; i < len; i++)
	{
		std::size_t found = paths[i].find("sounds");
		if(found != std::string::npos)
		{
			paths.erase(paths.begin()+i);
			break;
		}
	}
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	paths.push_back("../../Resources/shared/sounds/" + cat);
#else
	paths.push_back("shared/sounds/" + cat);
#endif

	for(auto path:paths)
	{
		log("path: %s", path.c_str());
	}

	FileUtils::getInstance()->setSearchPaths(paths);

	CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	std::vector<std::string> words = WordedApp::getAllWords(cat);
	for(std::string word : words)
		audioEngine->preloadEffect(word.c_str());	
}

void WordedApp::unloadSound(const std::string& cat)
{
	CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	std::vector<std::string> words = WordedApp::getAllWords(cat);
	for (std::string word : words)
		audioEngine->unloadEffect(word.c_str());
}

std::vector<std::string> WordedApp::getAllWords(const std::string& cat)
{
	Configuration* cfg = Configuration::getInstance();
	std::vector<std::string> v = util::common::splitStr(cfg->getValue(cat).asString().c_str(), ';');
	return v;
}

std::vector<std::string> WordedApp::getRndFormation(const std::string& cat, int total)
{
	std::vector<std::string> v = getAllWords(cat);
    std::vector<std::string> rndV = {};
	size_t len = v.size();
	while (total > len)
	{		
		auto vclone = v;
		int count = total - len;
		if (count > len)
			count = len;
		v.insert(v.end(), vclone.begin(), vclone.begin() + count);
		total = total - len;
	}
	len = v.size();
    while (len > 0 && total > 0)
	{
		int idx = rand() % len;
		std::string item = v.at(idx);
		util::common::trimSpace(item);
		if(item != " " && item != "")
			rndV.push_back(v[idx]);
		v.erase(v.begin() + idx);
		len = v.size();
        total--;
	}
    
	return rndV;
}

std::vector<std::string> WordedApp::getRndFormationExcept(const std::string& cat, const std::string& exc, int total)
{
    std::vector<std::string> v = getAllWords(cat);
    size_t len = v.size();
    for (size_t i = 0; i < len; i++)
    {
        if (v[i] == exc)
        {
            v.erase(v.begin() + i);
            len--;
            i--;
        }
    }
    std::vector<std::string> rndV = {};
    
    len = v.size();
    while (total > len)
    {
        auto vclone = v;
        int count = total - len;
        if (count > len)
            count = len;
        v.insert(v.end(), vclone.begin(), vclone.begin() + count);
        total = total - len;
    }
    len = v.size();
    while (len > 0 && total > 0)
    {
        int idx = rand() % len;
        std::string item = v.at(idx);
        util::common::trimSpace(item);
        if(item != " " && item != "")
            rndV.push_back(v[idx]);
        v.erase(v.begin() + idx);
        len = v.size();
        total--;
    }
	return rndV;
}

std::string WordedApp::getGCKey(const char* key)
{
#ifdef LITE
    return StringUtils::format("wlite_%s", key);
#else
    return std::string(key);
#endif
}

std::vector<std::string> WordedApp::getRndFormationWith(const std::string& cat, const std::string& with, int total)
{
	std::vector<std::string> v = getRndFormationExcept(cat, with, total - 1);
	int idx = rand()%total;
	if(idx == total-1)
		v.push_back(with);
	else
		v.insert(v.begin()+idx, with);
//	for (std::string str : v) {
//		log("words: %s", str.c_str());
//	}
	return v;
}
void WordedApp::initialize()
{	
	// load all data
	// cat idx
	Value adCatIdx = util::common::getValue(KEY_AD_IDX);
	if (adCatIdx.isNull())
	{
		adCatIdx = Value(-1);
		util::common::saveValue(KEY_AD_IDX, adCatIdx);		
	}
	else
	{

		int64_t timeStart = util::common::getValue(KEY_AD_START_TIME).asDouble();
		time_t currTime = time(NULL);
		if (currTime - timeStart > TIME_AD_REMAIN * 3600)
		{
			adCatIdx = Value(-1);
			util::common::saveValue(KEY_AD_IDX, adCatIdx);
		}
	}
	_adCatIdx = adCatIdx.asInt();
	// cat unlocked
	Value catUnlockedNum = util::common::getValue(KEY_NUM_CAT_UNLOCKED);
	if(catUnlockedNum.isNull())
	{
		catUnlockedNum = Value(BEGINNER_CAT_NUM);
		util::common::saveValue(KEY_NUM_CAT_UNLOCKED, catUnlockedNum);
	}	
	_unlockedCat = catUnlockedNum.asInt();

	// rate idx
	Value rateCatIdx = util::common::getValue(KEY_RATE_IDX);
	if (rateCatIdx.isNull())
	{
		rateCatIdx = Value(-1);
		util::common::saveValue(KEY_RATE_IDX, rateCatIdx);
	}
	else
	{
		int64_t timeStart = util::common::getValue(KEY_RATE_START_TIME).asDouble();
		time_t currTime = time(NULL);
		if (currTime - timeStart > TIME_AD_REMAIN * 3600)
		{
			rateCatIdx = Value(-1);
			util::common::saveValue(KEY_RATE_IDX, rateCatIdx);
		}
	}
	_rateCatIdx = rateCatIdx.asInt();
	// init rate remind
	Value rateRemind = util::common::getValue(KEY_REMIND_RATE);
	if (rateRemind.isNull())
	{
		rateRemind = Value(RATE_REMIND_ROUND);
		util::common::saveValue(KEY_REMIND_RATE, rateRemind);
	}
}

int WordedApp::getUnlockedCat()
{
	return _unlockedCat;
}

int WordedApp::getAdCat()
{
	return _adCatIdx;
}

bool WordedApp::checkShowRateDlg()
{
	Value build = util::common::getValue(KEY_ALREADY_RATE);
	if (build.isNull())
	{
		build = Value("-1");
		util::common::saveValue(KEY_ALREADY_RATE, build);
	}
	std::string realBuild = util::platform::getBuildVersion();
	if (realBuild != build.asString())
	{
		int valCountRate = util::common::getValue(KEY_REMIND_RATE).asInt();
		if (valCountRate < 0)
		{
			return true;
		}
	}
	return false;
}

bool WordedApp::validateAnswer(const std::string& item1, const std::string& item2)
{
	return item1 == item2;
}

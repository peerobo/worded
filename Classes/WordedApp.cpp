#include "WordedApp.h"
#include "base/Util.h"
#include <cocos2d.h>

USING_NS_CC;

const int WordedApp::DIFFICULT_EASY = 0;
const int WordedApp::DIFFICULT_HARD = 1;
const int WordedApp::ONE_MODE_TIME[2] = { 10, 5 };
const int WordedApp::ONE_MODE_LEVELS[2] = { 10, 10 };
const int WordedApp::ONE_MODE_PENALTY[2] = {-5,-5};
const float WordedApp::ONE_MODE_SCORE_RATIO[2] = {0.5f,2.0f};
const int WordedApp::TABLE_MODE_TIME[2] = { 15, 8};
const int WordedApp::TABLE_MODE_LEVELS[2] = { 10, 10};
const int WordedApp::TABLE_MODE_PENALTY[2] = {-4,-4};
const float WordedApp::TABLE_MODE_SCORE_RATIO[2] = {1.f/3.f, 1.25f};
const float WordedApp::TABLE_MODE_TIME_PAUSE_B4_COUNT = 2.f;
int WordedApp::difficult = WordedApp::DIFFICULT_EASY;

int WordedApp::_currCat = -1;
int WordedApp::_unlockedCat = 4;
bool WordedApp::_adCat = false;
int WordedApp::_adCatIdx = -1;

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

std::vector<std::string> WordedApp::getRndFormation(const std::string& cat, int total)
{
	Configuration* cfg = Configuration::getInstance();
	std::vector<std::string> v = util::common::splitStr(cfg->getValue(cat).asString().c_str(), ';');
	std::vector<std::string> rndV = std::vector<std::string>();
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
	while (len > 0)
	{
		int idx = rand() % len;
		std::string item = v.at(idx);
		util::common::trimSpace(item);
		if(item != "")
			rndV.push_back(v.at(idx));
		v.erase(v.begin() + idx);
		len = v.size();
	}
	return rndV;
}

std::vector<std::string> WordedApp::getRndFormationExcept(const std::string& cat, const std::string& exc, int total)
{
	auto v = getRndFormation(cat, total);
	int len = v.size();
	for (size_t i = 0; i < len; i++)
	{
		if (v[i] == exc)
		{
			v.erase(v.begin() + i);
			len--;
			i--;
		}
	}
	return v;
}

std::vector<std::string> WordedApp::getRndFormationWith(const std::string& cat, const std::string& with, int total)
{
	std::vector<std::string> v = getRndFormation(cat, total - 1);
	int idx = rand()%total;
	if(idx == total-1)
		v.push_back(with);
	else
		v.insert(v.begin()+idx, with);
	return v;
}

void WordedApp::initialize()
{	
	// load all data
}

void WordedApp::rndOneModeCat()
{
	ValueVector v = Configuration::getInstance()->getValue("cats").asValueVector();
	_currCat = rand() % (_unlockedCat+(_adCat ? 1 : 0));
	if (_currCat == _unlockedCat && _adCat)
	{
		_currCat = _adCatIdx;
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

Node* WordedApp::getScoreBoard(std::string cat, int score, int bestScore, std::function<void()> backCB, std::function<void()> retryCB)
{
	Node* container;
	return container;
}

bool WordedApp::validateAnswer(const std::string& item1, const std::string& item2)
{
	return item1 == item2;
}

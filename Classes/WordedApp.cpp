#include "WordedApp.h"
#include "base/Util.h"
#include <cocos2d.h>
#include "Constants.h"
#include <audio/include/SimpleAudioEngine.h>
#include <ui/UIButton.h>

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

void WordedApp::playSound(const std::string& cat, const std::string& word)
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
    Size s = util::graphic::getScreenSize();
    Node* container = Node::create();
    Configuration* cfg = Configuration::getInstance();
    
    std::string title = cfg->getValue("scoreCat").asString();
    std::string catTitle = cat;
    util::common::capitalize(catTitle);
    util::common::replace(title, "@cat", catTitle);
    Label* catLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, title);
    catLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    catLbl->setPosition(s.width/2, s.height - 250);
    util::effects::reveal(catLbl);
    container->addChild(catLbl,1);
    
    Label* descLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, cfg->getValue("scoreDesc").asString());
    descLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    descLbl->setPosition(s.width/2, s.height - 420);
    descLbl->setScale(0.8f);
    util::effects::reveal(descLbl);
    container->addChild(descLbl,1);
    
    Label* scoreLbl = Label::createWithBMFont(Constants::ASS_FNT_BIG, StringUtils::toString( score));
    scoreLbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scoreLbl->setPosition(s.width/2,s.height/2);
    util::effects::reveal(scoreLbl, 0.4f);
    container->addChild(scoreLbl,2);
    Rect rect = scoreLbl->getBoundingBox();
    
    Label* ptLbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, "pt");
    ptLbl->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    ptLbl->setPosition(rect.getMaxX(), rect.getMinY() + rect.size.height / 2);
    util::effects::reveal(ptLbl,0.4f);
    ptLbl->setScale(0.8f);
    container->addChild(ptLbl,1);
    
    Sprite* icoCheck = util::graphic::getSprite(Constants::ASS_ICO_CHECK);
    icoCheck->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    icoCheck->setPosition(rect.getMaxX(),rect.getMaxY() + rect.size.height/2);
    util::effects::blink(icoCheck,0.6f);
    icoCheck->setOpacity(0);
    container->addChild(icoCheck,3);
    
    std::string best;
    if(score > bestScore)
    {
        Sprite* highScore = util::graphic::getSprite(Constants::ASS_ICO_HIGHSCORE);
        highScore->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        highScore->setPosition(rect.getMaxX(),rect.getMaxY());
        highScore->setVisible(false);
        highScore->setScale(3);
        container->addChild(highScore,3);
        Vector<FiniteTimeAction*> vAct;
        vAct.pushBack(DelayTime::create(1));
        vAct.pushBack(Show::create());
        vAct.pushBack(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.3f));
        highScore->runAction(Sequence::create(vAct));
        best = cfg->getValue("newBestScore").asString();
    }
    else
    {
        best = cfg->getValue("bestScore").asString();
        util::common::replace(best, "@number", StringUtils::toString(bestScore));
    }
    
    Label* highScoreLabel = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, best);
    highScoreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    highScoreLabel->setPosition(rect.getMidX(), rect.getMinY() - 100);
    container->addChild(highScoreLabel,1);
    highScoreLabel->setScale(0.8f);
    util::effects::reveal(highScoreLabel,0.4f);
    
    
    auto backBt = ui::Button::create();
    container->addChild(backBt,3);
    backBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_BACK),ui::Widget::TextureResType::PLIST);
    backBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    backBt->setPosition(Vec2(s.width/2 - 200, 100));
    util::graphic::addClickBtCallback(backBt,backCB);
    
    
    auto shareBt = ui::Button::create();
    container->addChild(shareBt,3);
    shareBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_SHARE),ui::Widget::TextureResType::PLIST);
    shareBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    shareBt->setPosition(Vec2( s.width/2, 100));
    util::graphic::addClickBtCallback(shareBt, std::bind(&util::graphic::captureScreen));
    
    auto retryBt = ui::Button::create();
    container->addChild(retryBt,3);
    retryBt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BT_RETRY),ui::Widget::TextureResType::PLIST);
    retryBt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    retryBt->setPosition(Vec2(s.width/2 + 200,100));
    util::graphic::addClickBtCallback(retryBt, retryCB);
    
	return container;
}

bool WordedApp::validateAnswer(const std::string& item1, const std::string& item2)
{
	return item1 == item2;
}

#include "Util.h"
#include "Constants.h"
#include <cocostudio/CCSGUIReader.h>
#include "../GlobalVar.h"
#include <SimpleAudioEngine.h>
#include <iostream>
#include "cocos2d.h"
#include <regex>
#include <ctime>
#include "DlgMgr.h"

using namespace CocosDenshion;
static ValueVector listFiles;


void util_addSwallowTouch(Node* node)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		if (util_checkHit(touch, event->getCurrentTarget()))
		{
			return true;
		}
		return false;
	};
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

Vec2 util_convertPos(Node* node, Node* space)
{
	Vec2 newPoint = node->convertToWorldSpace(Vec2(0,0));
	return  space->convertToNodeSpace(newPoint);
}

void util_addClosedWhenClickOutside(Node* node, bool autoclean)
{
	// event
	auto listener = EventListenerTouchOneByOne::create();	
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		if (!util_checkHit(touch, event->getCurrentTarget()))
		{
			return true;
		}
		return false;
	};
	listener->onTouchEnded = [node, autoclean](Touch* touch, Event* event)
	{	
		if (!util_checkHit(touch, node))
		{
			node->removeFromParentAndCleanup(autoclean);			
		}
	};
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

void util_terminateApp()
{
	Director::getInstance()->end();
	exit(0);
}

void util_runAction(Node* node, Action* act)
{
	node->runAction(act);
}

void util_setBtEnable(ui::Button* bt, bool val, float opacity)
{
	bt->setOpacity(val ? 255 : opacity * 255);
	bt->setEnabled(val);
}


void util_showDisp(Node* node, bool withModalBG, int layer)
{
	Size nodeSize = node->getContentSize();
	Size scrSize = util_getScreenSize();
	Vec2 pt((nodeSize.width - scrSize.width) / 2, (nodeSize.height - scrSize.height) / 2);
	if (withModalBG)
	{
		if (!node->getChildByTag(1001))
		{
			auto bg = util_drawModalBG();
			bg->setTag(1001);
			bg->setPosition(pt);
			node->addChild(bg, 0);
		}
	}
	node->setPosition(Vec2(-pt.x, -pt.y));
	if (node->getParent() == NULL)
		GlobalVar::curScene->addChild(node, layer);	
}

void util_removeTexAtl(const std::string& texAtlName)
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(texAtlName + Constants::ASS_SUFFIX_DATA);
}

bool util_replace(std::string& sourceStr, const std::string& searchStr, const std::string& replaceStr)
{
	size_t start_pos = sourceStr.find(searchStr);
	bool found = false;
	while (start_pos != std::string::npos)
	{
		found = true;
		sourceStr.replace(start_pos, searchStr.length(), replaceStr);
		start_pos = sourceStr.find(searchStr);
	}
	
	return found;
}

void util_loadTexAtl(const std::string& nameTexAtl, bool removeAllCache)
{
	if (removeAllCache)
		SpriteFrameCache::getInstance()->removeSpriteFrames();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(nameTexAtl + Constants::ASS_SUFFIX_DATA, nameTexAtl + Constants::ASS_SUFFIX_TEXATL);
}

Sprite* util_getSprite(const std::string& sprFrameName)
{
	auto frm = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprFrameName + Constants::ASS_SUFFIX_IMAGE);
	if (frm)
		return Sprite::createWithSpriteFrame(frm);
	else
		return NULL;
}

Sprite* util_getSpriteFromImage(const std::string& imgName)
{
	return Sprite::create(imgName + Constants::ASS_SUFFIX_IMAGE);
}

Sprite* util_getSpriteFromImageJPG(const std::string& imgName)
{
	return Sprite::create(imgName + Constants::ASS_SUFFIX_IMAGE_JPG);
}

void util_resize4scr(Node* node, bool isFill)
{
	Size s = util_getScreenSize();
	Size ctSize = node->getContentSize();	
	float scale = 1;
	if (ctSize.width > s.width)
	{
		scale = (float)s.width / ctSize.width;
		node->setScale(scale);
	}
	if (!isFill)
	{			
		if (ctSize.height*scale > s.height)
			node->setScale(s.height / ctSize.height);
	}
	else
	{		
		if (ctSize.height*scale < s.height)
			node->setScale(s.height / ctSize.height);
	}
	
}

Size util_getScreenSize()
{
	return Director::getInstance()->getVisibleSize();
}

std::string util_getAssetName(const std::string& texName)
{
	return std::string(texName + Constants::ASS_SUFFIX_IMAGE);
}

bool util_checkHasFrameName(const char* name)
{
	std::string str(name);
	str.append(Constants::ASS_SUFFIX_IMAGE);
	return SpriteFrameCache::getInstance()->getSpriteFrameByName(str) != NULL;
}


std::string util_getCacheDirectory()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    std::string path = FileUtils::getInstance()->getWritablePath();
    size_t idx = path.find("Documents/");
    if(idx!= std::string::npos)
    {
        path.erase(idx);
    }
    path.append("Library/Caches/");
    return path;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    return "/Library/Caches/";
#else
    return FileUtils::getInstance()->getWritablePath();
#endif
}

std::string util_getTmpDirectory()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    std::string path = FileUtils::getInstance()->getWritablePath();
    size_t idx = path.find("Documents/");
    if(idx!= std::string::npos)
    {
        path.erase(idx);
    }
    path.append("tmp/");
    return path;
#else
    return FileUtils::getInstance()->getWritablePath();
#endif
}

void util_changeBtName(ui::Button* bt, const char* label)
{
	ui::TextBMFont* lbl = static_cast<ui::TextBMFont*>(bt->getChildByName("lbl"));
	lbl->setString(label);
}

std::string util_numberWithCommas(unsigned long long n)
{
	std::string s;
	int cnt = 0;
	do
	{
		s.insert(0, 1, char('0' + n % 10));
		n /= 10;
		if (++cnt == 3 && n)
		{
			s.insert(0, 1, '.');
			cnt = 0;
		}
	} while (n);
	return s;
}

void util_setOpacity(Node* object, GLubyte opaque)
{
	Vector<Node *> childs;	
	
	childs = object->getChildren();	
	object->setOpacity(opaque);
	if (childs.size()>0) 
	{
		for (Node* child : childs)
		{
			child->setOpacity(opaque);			
			if (child->getChildrenCount()>0)
				util_setOpacity(child, opaque);
			
		}
	}
}

bool util_checkTouchStill(Touch* t, int threshold)
{
	Vec2 pt = t->getLocation();
	Vec2 pt1 = t->getStartLocation();
	pt1.subtract(pt);
	return pt1.length() < threshold;
}

bool util_checkHitPt(Vec2 worldPt, Node* node)
{
	if (node == NULL)
		return false;
	Point p = worldPt;
	Point nsp = node->convertToNodeSpace(p);
	Rect bb;
	bb.size = node->getContentSize();
	bb.size.width = bb.size.width;
	bb.size.height = bb.size.height;
	if (bb.containsPoint(nsp) && node->isVisible())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool util_checkHit(Touch* touch, Node* node)
{
	if (node == NULL)
		return false;
	Point p = touch->getLocation();
	Point nsp = node->convertToNodeSpace(p);
	Rect bb;
	bb.size = node->getContentSize();
	bb.size.width = bb.size.width;
	bb.size.height = bb.size.height;
	if (bb.containsPoint(nsp) && node->isVisible())
	{		
		return true;
	}
	else
	{
		return false;
	}
}

Scene* util_createSceneWithLayer(Layer* layer)
{
	auto scene = Scene::create();
	scene->addChild(layer);
	layer->setTag(0);
	//layer->setKeyboardEnabled(true);
	EventListenerKeyboard* evt = EventListenerKeyboard::create();
	evt->onKeyReleased = CC_CALLBACK_2(Layer::onKeyReleased, layer);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evt, layer);

	return scene;
}

Node* util_drawRect(Rect rec, Color4F color)
{
	DrawNode* drawNode = DrawNode::create();
	Vec2 vecs[4] = { Vec2(rec.origin.x, rec.origin.y), Vec2(rec.origin.x + rec.size.width, rec.origin.y), Vec2(rec.origin.x + rec.size.width, rec.origin.y + rec.size.height), Vec2(rec.origin.x, rec.origin.y + rec.size.height) };
	drawNode->drawPolygon(vecs, 4, color, 1, color);
	return drawNode;
}

Node* util_drawModalBG()
{
	Size s = util_getScreenSize();

	DrawNode* drawNode = DrawNode::create();
	Vec2 vecs[4] = { Vec2(0, 0), Vec2(s.width, 0), Vec2(s.width, s.height), Vec2(0, s.height) };
	drawNode->drawPolygon(vecs, 4, Color4F(0, 0, 0, 0.6f), 1, Color4F(0, 0, 0, 0.6f));
	return drawNode;
}

uint32_t util_playSound(const char* snd, bool loop)
{
	if (!GlobalVar::myData.isEnableAudio)
		return -1;
	SimpleAudioEngine* ins = SimpleAudioEngine::getInstance();	
	return ins->playEffect(snd,loop);	
}

void util_playSoundNoResponse(const char* snd, bool loop)
{
	if (!GlobalVar::myData.isEnableAudio)
		return;
	SimpleAudioEngine* ins = SimpleAudioEngine::getInstance();
	ins->playEffect(snd, loop);
}

void util_playMusic(const char* music)
{
	if (!GlobalVar::myData.isEnableAudio)
		return;
	SimpleAudioEngine* ins = SimpleAudioEngine::getInstance();
	ins->playBackgroundMusic(music	, true);
}

void util_stopMusic(uint32_t id)
{
	SimpleAudioEngine* ins = SimpleAudioEngine::getInstance();
	ins->stopEffect(id);
	ins->stopBackgroundMusic();
}

void util_stopAllSounds()
{
	SimpleAudioEngine* ins = SimpleAudioEngine::getInstance();
	ins->stopAllEffects();
}


uint32_t _IPToUInt(const std::string ip) {
    int a, b, c, d;
    uint32_t addr = 0;

    if (sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d) != 4)
        return 0;

    addr = a << 24;
    addr |= b << 16;
    addr |= c << 8;
    addr |= d;
    return addr;
}

bool _IsIPInRange(const std::string ip, const std::string network, const std::string mask) {
    uint32_t ip_addr = _IPToUInt(ip);
    uint32_t network_addr = _IPToUInt(network);
    uint32_t mask_addr = _IPToUInt(mask);

    uint32_t net_lower = (network_addr & mask_addr);
    uint32_t net_upper = (net_lower | (~mask_addr));

    if (ip_addr >= net_lower &&
        ip_addr <= net_upper)
        return true;
    return false;
}

std::string _cidr2subnet(int idx)
{
	std::string subnet(Constants::CONST_CIDR[idx]);
	return subnet;
}

void _ipReturn(const char* data, size_t t, std::function<void(bool)> callback)
{
	std::string ip(data, data + t);
	log("ip %s", ip.c_str());
	int listLen = sizeof(Constants::CONST_IP_RANGE) / sizeof(const char*);
	bool isOK = false;
	for (int i = 0; i < listLen ; i++)
	{
		std::string networkIP = Constants::CONST_IP_RANGE[i];
		size_t idx = networkIP.find("/");
		if (idx < networkIP.length())
		{
			isOK = _IsIPInRange(ip, networkIP.substr(0, idx), _cidr2subnet(atoi(networkIP.substr(idx+1,networkIP.length()).c_str())));
		}
		if (isOK)
			break;
	}
	callback(isOK);
}


void util_trimSpace(std::string& sourceStr)
{		
	std::regex b("^\\s+");
	std::string rbegin = std::regex_replace(sourceStr, b, "");
	std::regex e("\\s+$");
	std::string rend = std::regex_replace(rbegin, e, "");
	std::regex m("\\s+");
	std::string rm = std::regex_replace(rend, m, " ", std::regex_constants::match_any);
	sourceStr = rm;
}




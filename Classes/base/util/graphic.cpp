#include "graphic.h"
#include "common.h"
#include "../../Constants.h"
#include  "../../GlobalVar.h"
#include "../Looper.h"

namespace util {
	void graphic::addSwallowTouch(Node* node)
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [](Touch* touch, Event* event)
		{
			if (checkHit(touch, event->getCurrentTarget()))
			{
				return true;
			}
			return false;
		};
		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
	}

	float graphic::fit(Node* fitTo, Node* toFit)
	{
		Size sFitTo = fitTo->getContentSize();
		Size sToFit = toFit->getContentSize();
		float scale = 1;
		if(sToFit.width > sFitTo.width)
			scale = sFitTo.width / sToFit.width;
		if(sToFit.height*scale > sFitTo.height)
			scale = sFitTo.height / sToFit.height;
		return scale;
	}
    
    float graphic::fit(cocos2d::Size fitTo, cocos2d::Node *toFit)
    {
        Size sToFit = toFit->getContentSize();
        float scale = 1;
        if(sToFit.width > fitTo.width)
            scale = fitTo.width / sToFit.width;
        if(sToFit.height*scale > fitTo.height)
            scale = fitTo.height / sToFit.height;
        return scale;
    }
    
    void graphic::addClickBtCallback(ui::Widget* bt, std::function<void()> cb)
    {
        using namespace std::placeholders;
        bt->addTouchEventListener(std::bind( &graphic::onBtTouch, _1,_2, cb));
    }
    
    void graphic::onBtTouch(Ref* r, ui::Widget::TouchEventType type, std::function<void()> cb)
    {
        if(type == ui::Widget::TouchEventType::ENDED)
        {
            cb();
        }
    }
    
    void graphic::captureScreen()
    {
		std::string cachePath = common::getCacheDirectory();
		cachePath += "/screenshot.png";
		utils::captureScreen([](bool ret, const std::string& file) {}, cachePath);
    }
    
	Vec2 graphic::convertPos(Node* node, Node* space)
	{
		Vec2 newPoint = node->convertToWorldSpace(Vec2(0, 0));
		return  space->convertToNodeSpace(newPoint);
	}

	void graphic::runAction(Node* node, Action* act)
	{
		node->runAction(act);
	}

	void graphic::loadTexAtl(const std::string& texAtlName, bool removeAllCache)
	{
		if (removeAllCache)
			SpriteFrameCache::getInstance()->removeSpriteFrames();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(texAtlName + Constants::ASS_SUFFIX_DATA, texAtlName + Constants::ASS_SUFFIX_TEXATL);
	}

	void graphic::removeTexAtl(const std::string& texAtlName)
	{
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(texAtlName + Constants::ASS_SUFFIX_DATA);
	}

	std::string graphic::getAssetName(const std::string& texName)
	{
		return std::string(texName + Constants::ASS_SUFFIX_IMAGE);
	}

	bool graphic::checkHasFrameName(const char* name)
	{
		std::string str(name);
		str.append(Constants::ASS_SUFFIX_IMAGE);
		return SpriteFrameCache::getInstance()->getSpriteFrameByName(str) != NULL;
	}

	void graphic::setOpacity(Node* object, GLubyte opaque)
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
					setOpacity(child, opaque);
			}
		}
	}

	bool graphic::checkHit(Touch* touch, Node* node)
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

	bool graphic::checkHitPt(Vec2 worldPt, Node* node)
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

	bool graphic::checkTouchStill(Touch* t, int threshold)
	{
		Vec2 pt = t->getLocation();
		Vec2 pt1 = t->getStartLocation();
		pt1.subtract(pt);
		return pt1.length() < threshold;
	}

	Scene* graphic::createSceneWithLayer(Layer* layer)
	{
		auto scene = Scene::create();
		if(!Looper::instance )
		{
			Looper::create();
		}
        else
        {
            Looper::instance->removeFromParentAndCleanup(false);
        }
		scene->addChild(Looper::instance);
		scene->addChild(layer);
		layer->setTag(0);

		return scene;
	}

	void graphic::changeSceneWithLayer(Layer* layer)
	{
		GlobalVar::curScene = layer;
		Director::getInstance()->replaceScene(createSceneWithLayer(layer));
	}

	void graphic::generateLayerWithTag(Node* p, std::vector<int> layerTags, int startZ)
	{
		int index = startZ;
		for (int tag : layerTags)
		{
			auto n = Node::create();
			n->setTag(tag);
			p->addChild(n, index++);
		}
	}

	void graphic::resize4scr(Node* node, bool isFill)
	{
		Size s = getScreenSize();
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

	Sprite* graphic::getSpriteFromImage(const std::string& imgName)
	{
		return Sprite::create(imgName + Constants::ASS_SUFFIX_IMAGE);
	}

	Sprite* graphic::getSpriteFromImageJPG(const std::string& imgName)
	{
		return Sprite::create(imgName + Constants::ASS_SUFFIX_IMAGE_JPG);
	}

	Node* graphic::drawRect(Rect rec, Color4F color)
	{
		DrawNode* drawNode = DrawNode::create();
		Vec2 vecs[4] = { Vec2(rec.origin.x, rec.origin.y), Vec2(rec.origin.x + rec.size.width, rec.origin.y), Vec2(rec.origin.x + rec.size.width, rec.origin.y + rec.size.height), Vec2(rec.origin.x, rec.origin.y + rec.size.height) };
		drawNode->drawPolygon(vecs, 4, color, 1, color);
		return drawNode;
	}

	Node* graphic::drawModalBG()
	{
		Size s = getScreenSize();

		DrawNode* drawNode = DrawNode::create();
		Vec2 vecs[4] = { Vec2(0, 0), Vec2(s.width, 0), Vec2(s.width, s.height), Vec2(0, s.height) };
		drawNode->drawPolygon(vecs, 4, Color4F(0, 0, 0, 0.6f), 1, Color4F(0, 0, 0, 0.6f));
		return drawNode;
	}

	void graphic::showDisp(Node* node, bool withModalBG, int layer)
	{
		Size nodeSize = node->getContentSize();
		Size scrSize = getScreenSize();
		Vec2 pt((nodeSize.width - scrSize.width) / 2, (nodeSize.height - scrSize.height) / 2);
		if (withModalBG)
		{
			if (!node->getChildByTag(1001))
			{
				auto bg = drawModalBG();
				bg->setTag(1001);
				bg->setPosition(pt);
				node->addChild(bg, 0);
			}
		}
		node->setPosition(Vec2(-pt.x, -pt.y));
		if (node->getParent() == NULL)
			GlobalVar::curScene->addChild(node, layer);
	}

	void graphic::setBtEnable(ui::Button* bt, bool val, float opacity)
	{
		bt->setOpacity(val ? 255 : opacity * 255);
		bt->setEnabled(val);
	}

	void graphic::addClosedWhenClickOutside(Node* node, bool autoclean)
	{
		// event
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [](Touch* touch, Event* event)
		{
			if (!checkHit(touch, event->getCurrentTarget()))
			{
				return true;
			}
			return false;
		};
		listener->onTouchEnded = [node, autoclean](Touch* touch, Event* event)
		{
			if (!checkHit(touch, node))
			{
				node->removeFromParentAndCleanup(autoclean);
			}
		};
		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
	}

	Sprite* graphic::getSprite(const std::string& sprFrameName)
	{
		auto frm = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprFrameName + Constants::ASS_SUFFIX_IMAGE);
		if (frm)
			return Sprite::createWithSpriteFrame(frm);
		else
			return NULL;
	}

	Size graphic::getScreenSize()
	{
		return Director::getInstance()->getVisibleSize();
	}

	void graphic::addNodeClickCallback(Node* node, std::function<void()> cb, bool swallowTouch)
	{
		auto evtL = EventListenerTouchOneByOne::create();
		using namespace std::placeholders;
		evtL->onTouchBegan = std::bind(&graphic::onNodeTouchBegan,_1,_2);
		evtL->onTouchEnded = std::bind(&graphic::onNodeTouchEnded,_1,_2, cb);
		evtL->setSwallowTouches(swallowTouch);
		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evtL, node);
	}

	bool graphic::onNodeTouchBegan(Touch* t, Event* e)
	{
		if (checkHit(t, e->getCurrentTarget()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void graphic::onNodeTouchEnded(Touch* t, Event* e, std::function<void()> cb)
	{
		if (checkTouchStill(t))
		{
			cb();
		}
	}
}

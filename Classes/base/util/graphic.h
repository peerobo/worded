#pragma once
#include <cocos2d.h>
#include <ui/UIButton.h>

USING_NS_CC;

namespace util
{
	class graphic
	{
		public:
		static void addSwallowTouch(Node* node);
		static Vec2 convertPos(Node* node, Node* space);
		static void runAction(Node* node, Action* act);
		static void loadTexAtl(const std::string& texAtlName, bool removeAllCache);
		static void removeTexAtl(const std::string& texAtlName);
		static std::string getAssetName(const std::string& texName);
		static bool checkHasFrameName(const char* name);
		static void setOpacity(Node* object, GLubyte opaque);
		static bool checkHit(Touch* touch, Node* node);
		static bool checkHitPt(Vec2 worldPt, Node* node);
		static bool checkTouchStill(Touch* t, int threshold = 80);
		static Scene* createSceneWithLayer(Layer* layer);
		static void changeSceneWithLayer(Layer* layer);
		static void resize4scr(Node* node, bool isFill);
		static Sprite* getSpriteFromImage(const std::string& imgName);
		static Sprite* getSpriteFromImageJPG(const std::string& imgName);
		static Node* drawRect(Rect rec, Color4F color);
		static Node* drawModalBG();
		static void showDisp(Node* node, bool withModalBG, int layer = 100);
		static void setBtEnable(ui::Button* bt, bool val, float opacity = 0.2f);
		static void addClosedWhenClickOutside(Node* node, bool autoclean = true);
		static Sprite* getSprite(const std::string& sprFrameName);
		static Size getScreenSize();
		static void generateLayerWithTag(Node* p, std::vector<int> layerTags, int startZ = 0);
		static float fit(Node* fitTo, Node* toFit);
	};
}

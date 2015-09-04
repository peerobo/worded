#pragma once
#include <string>
#include <ostream>
#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIWidget.h"
#include "ui/UITextBMFont.h"
USING_NS_CC;
std::string util_getCacheDirectory();
std::string util_getTmpDirectory();
void util_addSwallowTouch(Node* node);
Vec2 util_convertPos(Node* node, Node* space);

void util_terminateApp();
void util_runAction(Node* node, Action* act);
bool util_replace(std::string& sourceStr, const std::string& searchStr, const std::string& replaceStr);
void util_trimSpace(std::string& sourceStr);
std::string util_getAvaUrlFB(std::string& uid);
void util_loadTexAtl(const std::string& texAtlName, bool removeAllCache);
void util_removeTexAtl(const std::string& texAtlName);
std::string util_getAssetName(const std::string& texName);
Sprite* util_getSprite(const std::string& sprFrameName);
Size util_getScreenSize();
bool util_checkHasFrameName(const char* name);
void util_changeBtName(ui::Button* bt,const char* name);
std::string util_numberWithCommas(unsigned long long n);
void util_setOpacity(Node* object, GLubyte opaque);
bool util_checkHit(Touch* touch, Node* node);
bool util_checkHitPt(Vec2 worldPt, Node* node);
bool util_checkTouchStill(Touch* t, int threshold = 80);
Scene* util_createSceneWithLayer(Layer* layer);
void util_resize4scr(Node* node, bool isFill);
Sprite* util_getSpriteFromImage(const std::string& imgName);
Sprite* util_getSpriteFromImageJPG(const std::string& imgName);
Node* util_drawRect(Rect rec, Color4F color);
Node* util_drawModalBG();
/*
remember to delete result char
*/
uint32_t util_playSound(const char* snd, bool loop);
void util_playSoundNoResponse(const char* snd, bool loop);
uint32_t util_playMusic(const char* music, bool loop); 
void util_stopMusic(uint32_t id);
void util_mute();
void util_showDisp(Node* node, bool withModalBG, int layer = 100);
void util_setBtEnable(ui::Button* bt, bool val, float opacity = 0.2f);
void util_addClosedWhenClickOutside(Node* node, bool autoclean = true);


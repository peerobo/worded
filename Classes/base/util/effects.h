#pragma once
#include <cocos2d.h>

namespace util 
{
	class effects
	{
	public:
		// fade out and fade in multiple time
		static void blink(cocos2d::Node* node, std::function<void()> cb = nullptr);
		// move up and fade in
		static void reveal(cocos2d::Node* node, float delay = -1, std::function<void()> cb = nullptr);
		// move to the left and remove self
		static void disappear(cocos2d::Node* node, float delay = -1, std::function<void()> cb = nullptr);
	};
}

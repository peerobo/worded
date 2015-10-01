#pragma once
#include <string>
#include <functional>

namespace util 
{
	class ad
	{
	public:
		static void initLeadbolt(const std::string& apikey);		
        static void initVungle(const std::string& appid);
        static void showVungle(std::function<void(bool)> onShownCB = nullptr, std::function<void(bool)> onRewardCB = nullptr);
		static void showLeadboltAd();
		static bool isVideoAdAvailable();
	};

}
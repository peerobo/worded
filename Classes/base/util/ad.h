#pragma once
#include <string>

namespace util 
{
	class ad
	{
	public:
		static void initLeadbolt(const std::string& apikey);
		static void showLeadboltAd();
        static void initVungle(const std::string& appid);
        static void showVungle();
	};

}
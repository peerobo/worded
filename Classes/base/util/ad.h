#pragma once
#include <string>

namespace util 
{
	class ad
	{
	public:
		static void initLeadbolt(const std::string& apikey);		
        static void initVungle(const std::string& appid);
        static void showVungle();
		static void showLeadboltAd();
	};

}
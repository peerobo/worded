#pragma once
#include <string>

namespace util 
{
	class ad
	{
	public:
		static void initLeadbolt(std::string apikey);
		static void showLeadboltAd();
        static void initVungle();
        static void showVungle();
	};

}
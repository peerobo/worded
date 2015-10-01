#pragma once
#include <string>
#include <stdio.h>
#include <functional>
namespace util
{
	class platform
	{
	public:
		static void vibrate();
        static void rate();
		static void openURL(const std::string& url);
        static void authenGC();
        static bool isGC();
        static void showGC();
        static void setScoreGC(const std::string& cat, int score);
        static void saveToAlbum(const std::string& fileURL);
        static void updateAchGC(const std::string& ach, float percent, std::function<void()> okCB = nullptr);
        static void resetAchGC();
		static bool share2Twitter(const std::string& imagePath, const std::string msg);
		static bool share2FB(const std::string& imagePath, const std::string msg);
		static std::string getBuildVersion();
	};
	
}

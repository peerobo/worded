#pragma once
#include <string>
namespace util
{
	class platform
	{
	public:
		static void vibrate();
        static void rate();
        static void authenGC();
        static bool isGC();
        static void showGC();
        static void setScoreGC(const std::string& cat, int score);
        static void saveToAlbum(const std::string& fileURL);
		static void updateAchGC(const std::string& ach, float percent);
	};
	
}

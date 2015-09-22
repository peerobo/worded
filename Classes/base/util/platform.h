#pragma once

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
	};
	
}

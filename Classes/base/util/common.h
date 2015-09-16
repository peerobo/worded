#pragma once
#include <cocos2d.h>

namespace util
{
	class common
	{
	public:
		static std::string getCacheDirectory();
		static std::string getTmpDirectory();
		static void terminateApp();
		static bool replace(std::string& sourceStr, const std::string& searchStr, const std::string& replaceStr);
		static void trimSpace(std::string& sourceStr);
		static std::string numberWithCommas(unsigned long long n);
		static uint32_t playSound(const char* snd, bool loop);
		static void playSoundNoResponse(const char* snd, bool loop);
		static void playMusic(const char* music);
		static void stopAllSounds(bool fadeOut = false);
		static std::vector<std::string> splitStr(const char* source, char delim);
		static void capitalize(std::string& str);
	};
}

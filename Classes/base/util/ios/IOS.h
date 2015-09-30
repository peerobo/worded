#pragma once

class IOS {
public:
    static bool isGC;
    static bool isVungleAvailable;
    static std::function<void(bool)> vungleShownCB;
    static std::function<void(bool)> vungleRewardCB;
    
	static void vibrate();
    static void rate(const std::string& appid);
    static void authenGC();
    static void showGC();
    static void setScoreGC(const std::string& cat, int score);
    static void saveToAlbum(const std::string& filePath);
    static void updateGCAchievement(const std::string& ach, float percent, std::function<void()> okCB);
    static bool share2Twitter(const std::string& path,const std::string& msg, const std::string& url);
    static bool share2Facebook(const std::string& path,const std::string& msg, const std::string& url);
    static void resetAchievement();
    static void vungleInit(const std::string& appID);
    static void vungleShow();
	static std::string getBuildVer();
};
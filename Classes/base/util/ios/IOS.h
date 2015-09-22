#pragma once

class IOS {
public:
    static bool isGC;
	static void vibrate();
    static void rate(const std::string& appid);
    static void authenGC();
    static void showGC();
    static void setScoreGC(const std::string& cat, int score);
};
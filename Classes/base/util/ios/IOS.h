#pragma once

class IOS {
private:
    static bool isGC;
public:
	static void vibrate();
    static void rate(std::string appid);
    static void authenGC();
};
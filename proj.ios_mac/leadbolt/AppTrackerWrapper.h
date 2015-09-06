//
//  AppFireworkWrapper.h
//  HelloCpp
//
//  Created by Tech on 1/10/13.
//
//

#ifndef __AppTrackerWrapper__
#define __AppTrackerWrapper__

#include "cocos2d.h"

class AppTrackerWrapper
{
public:
    static void startSession(const char* apiKey);
    static void loadModule(const char* placement);
    static void loadModule(const char* placement, const char * userData);
    static void loadModuleToCache(const char* placement);
    static void loadModuleToCache(const char* placement, const char * userData);
    static void destroyModule();
    static void fixAdOrientation(int orientation);

    static void event(const char* name);
    static void event(const char* name, float floatValue);

    static void transaction(const char* name, float floatValue, const char* currencyCode);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void closeSession(bool sync);
    static void pause();
    static void resume();
#else
    static void closeSession();
    static void setCrashHandlerStatus(bool enable);
#endif    

};

#endif /* defined(__AppTrackerWrapper__) */

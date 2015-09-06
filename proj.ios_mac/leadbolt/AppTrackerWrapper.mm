#include "AppTrackerWrapper.h"
#include "AppTracker.h" 
#import <platform/ios/CCEAGLView-ios.h>
#import "cocos2d.h"

static UIViewController * getViewController()
{
    return [UIApplication sharedApplication].keyWindow.rootViewController;
}

void AppTrackerWrapper::startSession(const char* apiKey)
{
    [AppTracker startSession:[NSString stringWithUTF8String:apiKey]];
}

void AppTrackerWrapper::closeSession()
{
    [AppTracker closeSession];
}

void AppTrackerWrapper::event(const char* name)
{
    [AppTracker event:[NSString stringWithUTF8String:name]];
}

void AppTrackerWrapper::event(const char* name, float floatValue)
{
    [AppTracker event:[NSString stringWithUTF8String:name] value:floatValue];
}

void AppTrackerWrapper::transaction(const char* name, float floatValue, const char* currencyCode)
{
    [AppTracker transaction:[NSString stringWithUTF8String:name] value:floatValue currencyCode:[NSString stringWithUTF8String:currencyCode]];
}

void AppTrackerWrapper::loadModule(const char* placement)
{
      [AppTracker loadModule:[NSString stringWithUTF8String:placement] viewController:getViewController()];
}

void AppTrackerWrapper::loadModule(const char* placement,const char* userData)
{
      [AppTracker loadModule:[NSString stringWithUTF8String:placement] viewController:getViewController() withUserData:[NSString stringWithUTF8String:userData]];
}

void AppTrackerWrapper::loadModuleToCache(const char* placement)
{
      [AppTracker loadModuleToCache:[NSString stringWithUTF8String:placement]];
}

void AppTrackerWrapper::loadModuleToCache(const char* placement,const char* userData)
{
      [AppTracker loadModuleToCache:[NSString stringWithUTF8String:placement] withUserData:[NSString stringWithUTF8String:userData]];
}

void AppTrackerWrapper::setCrashHandlerStatus(bool enable)
{
    [AppTracker setCrashHandlerStatus:enable];
} 

void AppTrackerWrapper::fixAdOrientation(int orientation)
{
    [AppTracker fixAdOrientation:(AdOrientation)(orientation)];
}

void AppTrackerWrapper::destroyModule()
{
    [AppTracker destroyModule];
}
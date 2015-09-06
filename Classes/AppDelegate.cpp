#include "AppDelegate.h"
#include "base/Util.h"
#include "IntroScreen.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

    ZipUtils::setPvrEncryptionKeyPart(0, 0xfc5cc0ed);
}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    ZipUtils::setPvrEncryptionKeyPart(1, 0x15b97c42);
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    ZipUtils::setPvrEncryptionKeyPart(3, 0x3e26102b);
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("1st", Rect(0, 0, 320, 480));
#else
        glview = GLViewImpl::create("1st");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    int w, h;
    int sw = glview->getFrameSize().width;
    int sh = glview->getFrameSize().height;
    int maxSize = sw < sh ? sh : sw;
    float scale;
    std::string	assetPath;
    ResolutionPolicy resPolicy = ResolutionPolicy::EXACT_FIT;
    if (maxSize <= 480)
    {
        w = sw / 0.25;
        h = sh / 0.25;
        scale = 0.25;
        assetPath = "@1x";
    }
    else if (maxSize <= 1024)
    {
        w = sw / 0.5;
        h = sh / 0.5;
        scale = 0.5;
        assetPath = "@2x";
    }
    else if (maxSize <= 1334)
    {
        w = sw / 1;
        h = sh / 0.67;
        scale = 1;
        assetPath = "@4x";
        resPolicy = ResolutionPolicy::FIXED_HEIGHT;
    }
    else
    {
        w = sw;
        h = sh;
        scale = 1;
        assetPath = "@4x";
    }
    glview->setDesignResolutionSize(w, h, resPolicy);
    director->setContentScaleFactor(scale);
    std::vector<std::string> paths;
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		paths.push_back("../../Resources/" + assetPath);
		paths.push_back("../../Resources/shared");
	}
	else
	{
		paths.push_back(assetPath);
		paths.push_back("shared");
	}
    
    FileUtils::getInstance()->setSearchPaths(paths);
    ZipUtils::setPvrEncryptionKeyPart(2, 0x51ce7d9e);
    register_all_packages();

    Configuration::getInstance()->loadConfigFile("localization.plist");
    // create a scene. it's an autorelease object
    auto scene = util_createSceneWithLayer(IntroScreen::create());

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

#include "AppDelegate.h"
#include "base/Util.h"
#include "IntroScreen.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
#include "GlobalVar.h"
#include "tablemode/CatChooser.h"
#include "base/ScoreDB.h"
#include "WordedApp.h"

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

	util::ad::initLeadbolt("PKOi4AX2StGGZquCKi4j461SHNG5GOHI");

    ZipUtils::setPvrEncryptionKeyPart(3, 0x3e26102b);	

	srand(time(NULL));
    
    // initialize director
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
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 40);
    
    int w, h;
    int sw = glview->getFrameSize().width;
    int sh = glview->getFrameSize().height;
    int maxSize = sw < sh ? sh : sw;
    float scale;
    std::string	assetPath;
    ResolutionPolicy resPolicy = ResolutionPolicy::EXACT_FIT;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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
#else
    int minSize = sw < sh ? sw : sh;
	if (minSize <= 240)
	{
		w = sw / 0.25;
		h = sh / 0.17;
		scale = 0.25;
		assetPath = "@1x";
		resPolicy = ResolutionPolicy::FIXED_HEIGHT;
	}
	else if (minSize <= 320)
	{
		w = sw / 0.25;
		h = sh / 0.25;
		scale = 0.25;
		assetPath = "@1x";
	}
	else if (minSize <= 480)
	{
		/*w = sw / 0.375;
		h = sh / 0.375;
		scale = 0.375;
		assetPath = "@1.5x";*/
		w = sw / 0.5;
		h = sh / 0.375;
		scale = 0.5;
		assetPath = "@2x";
		resPolicy = ResolutionPolicy::FIXED_HEIGHT;
	}
	else if (minSize <= 800)
	{
		w = sw / 0.5;
		h = sh / 0.5;
		scale = 0.5;
		assetPath = "@2x";
	}
	else if (minSize <= 1080)
	{
		/*w = sw / 0.75;
		h = sh / 0.75;
		scale = 0.75;
		assetPath = "@x";*/
		w = sw / 1;
		h = sh / 0.75;
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
#endif
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
	paths.push_back(util::common::getCacheDirectory());

    FileUtils::getInstance()->setSearchPaths(paths);
    ZipUtils::setPvrEncryptionKeyPart(2, 0x51ce7d9e);
    register_all_packages();
    util::platform::authenGC();
    Configuration::getInstance()->loadConfigFile("localization.plist");
    util::graphic::loadTexAtl(Constants::ASS_TEX_GUI, false);
	util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_ONE);
	util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_TABLE);
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->preloadBackgroundMusic(Constants::ASS_SND_THEME);
	audioEngine->setEffectsVolume(1);
	audioEngine->setBackgroundMusicVolume(1);
	audioEngine->preloadEffect(Constants::ASS_SND_INCREASE);
	audioEngine->preloadEffect(Constants::ASS_SND_ENDGAME);
	audioEngine->preloadEffect(Constants::ASS_SND_HIGHSCORE);
	audioEngine->preloadEffect(Constants::ASS_SND_CLICK);
	audioEngine->preloadEffect(Constants::ASS_SND_TIMEOUT);
	audioEngine->preloadEffect(Constants::ASS_SND_WRONGANSWER);
	// load data
	(new ScoreDB())->loadDB();
	GlobalVar::myData.isEnableVibration = util::common::getValue(Constants::KEY_VIBRATION).asBool();
	WordedApp::difficult = util::common::getValue(Constants::KEY_HARDMODE).asBool() ? WordedApp::DIFFICULT_HARD : WordedApp::DIFFICULT_EASY;
    // create a scene. it's an autorelease object
	GlobalVar::curScene = IntroScreen::create();
    auto scene = util::graphic::createSceneWithLayer(GlobalVar::curScene);
    // run
    director->runWithScene(scene);	

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    bool checkBGMusic = false;
    checkBGMusic = checkBGMusic || dynamic_cast<CatChooser*>(GlobalVar::curScene)
    		|| dynamic_cast<IntroScreen*>(GlobalVar::curScene);
    if(checkBGMusic)
    	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

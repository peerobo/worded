#include "MatchingScreen.h"
#include "MatchingLogic.h"
#include "../GlobalVar.h"
#include "../base/Util.h"
#include "../WordedApp.h"
#include "../Constants.h"

MatchingScreen::~MatchingScreen()
{	
	if(GlobalVar::gameLogic)
	{
		auto gl = static_cast<MatchingLogic*>(GlobalVar::gameLogic);
		std::string cat = gl->getCurrCat();
		util::graphic::removeTexAtl(cat);
		WordedApp::unloadSound(cat);
		if (gl)
		{
			gl->kill();
			CC_SAFE_DELETE(gl);
		}
	}	
}

MatchingScreen::MatchingScreen():ICON_LAYER(4), LABEL_LAYER(3), GUI_LAYER(2)
{
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_MATCHING);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 1);
	bg->setTag(1);

	/*Vector<FiniteTimeAction*> vec;
	vec.pushBack(DelayTime::create(0.1f));
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(TableScreen::animateIn, this)));
	runAction(Sequence::create(vec));*/

	std::vector<int> layers = { GUI_LAYER, ICON_LAYER, LABEL_LAYER };
	util::graphic::generateLayerWithTag(this, layers, 1);
}
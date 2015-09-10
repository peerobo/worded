#include "OneScreen.h"
#include "../base/Util.h"
#include "../Constants.h"

OneScreen::OneScreen() : LAYER_GUI(2), LAYER_LBL(3), LAYER_CAT(4)
{
	auto bg = util::graphic::getSpriteFromImageJPG(Constants::ASS_BG_ONE);
	Size s = util::graphic::getScreenSize();
	bg->setPosition(s.width / 2, s.height / 2);
	addChild(bg, 1);
	bg->setTag(1);

	util::common::stopAllSounds();

	std::vector<int> v({ LAYER_GUI,LAYER_LBL,LAYER_CAT });
	util::graphic::generateLayerWithTag(this, v, 2);

	animateIn();
}

void OneScreen::animateIn()
{
    
}
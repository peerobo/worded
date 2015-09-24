#include "PageIndicator.h"
#include "../Util.h"

PageIndicator::PageIndicator(const std::string& curPageFrame, const std::string& pageFrame)
{
	_curPage = -1;
	_totalPage = -1;
	curFrame = curPageFrame;
	frame = pageFrame;

	scheduleUpdate();
}

void PageIndicator::update(float dt)
{
	if (_totalPage != totalPage)
	{
		int spacing = 30;
		removeAllChildren();
		Size sIcon;
		int posX = 0;
		for (size_t i = 0; i < totalPage; i++)
		{			
			Sprite* spr = util::graphic::getSprite(frame);
			spr->setTag(10+i);
			spr->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			addChild(spr);
			spr->setPositionX(posX);
			if (i == 0)
			{
				sIcon = spr->getContentSize();
			}
			posX += sIcon.width + spacing;
		}
		
		setContentSize(Size(posX - spacing, sIcon.height));
		_totalPage = totalPage;
	}
	if (_curPage != curPage)
	{
		auto oldPage = dynamic_cast<Sprite*>(getChildByTag(10+_curPage));
		if(oldPage)
			oldPage->setSpriteFrame(util::graphic::getAssetName(frame));
		auto newPage = dynamic_cast<Sprite*>(getChildByTag(10+ curPage));
		if(newPage)
			newPage->setSpriteFrame(util::graphic::getAssetName( curFrame));
		_curPage = curPage;
	}
}

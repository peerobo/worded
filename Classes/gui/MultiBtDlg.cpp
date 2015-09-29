#include "MultiBtDlg.h"
#include "../base/Util.h"
#include "../Constants.h"

void MultiBtDlg::onBtClick(int idx)
{

}

void MultiBtDlg::setData(const std::string& title, const std::string& msg, std::vector<std::string> bts)
{
	removeAllChildren();
	
	auto bg = util::graphic::getSprite(Constants::ASS_BG_DLG_TEXT);
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Size size = bg->getContentSize();
	addChild(bg, 1);

	auto lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, title);	
	addChild(lbl, 2);
	lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lbl->setPosition(size.width / 2, size.height - 140);
	lbl->setColor(Color3B::BLACK);

	lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, msg);	
	addChild(lbl, 2);
	lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lbl->setPosition(size.width / 2, size.height/2 - 120);
	lbl->setColor(Color3B::BLACK);
	lbl->setScale(0.8f);
	lbl->setMaxLineWidth(size.width / 0.9f );

	size_t sizeBTs = bts.size();
	for (size_t i = 0; i < sizeBTs; i++)
	{		
		// create bt
		auto bt = ui::Button::create();
		if(i < sizeBTs-1)
			bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BG_DLG_BT_MID), ui::Widget::TextureResType::PLIST);
		else
			bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BG_DLG_BT), ui::Widget::TextureResType::PLIST);
		bt->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bt->setZoomScale(0);
		Size btSize = bt->getContentSize();				
		bt->setPosition(Vec2(0, 0));
		// shift old children
		auto exist = this->getChildren();
		for (auto c : exist)
		{
			c->setPositionY( c->getPositionY()+btSize.height);
		}
		// update dlg size
		size.height += btSize.height;
		addChild(bt, 1);
		// add bt callback
		util::graphic::addClickBtCallback(bt, CC_CALLBACK_0(MultiBtDlg::onBtClick, this, i));
		// add label
		lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, bts[i]);
		lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		lbl->setScale(0.8f);
		addChild(lbl, 2);
		lbl->setPosition(btSize.width / 2, btSize.height / 2);
		lbl->setColor(Constants::COLOR_LIGHT_BLUE);
	}
	
	this->setContentSize(size);
	util::graphic::addSwallowTouch(this);
	util::graphic::addClosedWhenClickOutside(this);
}

void MultiBtDlg::show()
{
	DlgMgr::getInstance()->showDlg(this);
}
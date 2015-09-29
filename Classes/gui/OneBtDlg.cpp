#include "OneBtDlg.h"
#include "../Constants.h"
#include "../base/Util.h"
#include <ui/UIButton.h>

OneBtDlg::OneBtDlg()
{
	auto bg = util::graphic::getSprite(Constants::ASS_BG_DLG_TEXT);
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	auto bt = ui::Button::create();
	bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BG_DLG_BT),ui::Widget::TextureResType::PLIST);
	bt->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bt->setZoomScale(0);
	Size size = bt->getContentSize();
	bg->setPosition(Vec2(0, size.height));	
	size.height += bg->getContentSize().height;
	bt->setPosition(Vec2(0, 0));
	this->setContentSize(size);
	addChild(bg, 1);
	addChild(bt, 1);
	util::graphic::addSwallowTouch(this);
	util::graphic::addClosedWhenClickOutside(this);
	util::graphic::addClickBtCallback(bt, CC_CALLBACK_0(OneBtDlg::onBtClick, this));
}

void OneBtDlg::setData(const std::string& title, const std::string& closebt)
{
	Size s = this->getContentSize();
	Label* lbl = dynamic_cast<Label*>(getChildByTag(2));
	if (!lbl)
	{
		lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, title);
		lbl->setTag(2);
		addChild(lbl, 2);
		lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		lbl->setPosition(s.width / 2, s.height - 160);
		lbl->setColor(Color3B::BLACK);
	}
	lbl->setString(title);

	lbl = dynamic_cast<Label*>(getChildByTag(3));
	if (!lbl)
	{
		lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, closebt);
		lbl->setTag(2);
		lbl->setScale(0.8f);
		addChild(lbl, 2);
		lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		lbl->setPosition(s.width / 2, 140);
		lbl->setColor(Constants::COLOR_LIGHT_BLUE);
	}
	lbl->setString(closebt);
}

void OneBtDlg::onBtClick()
{
	if (onBtClickCB)
		onBtClickCB();
	DlgMgr::getInstance()->closeDlg(this);
}

void OneBtDlg::show()
{
	DlgMgr::getInstance()->showDlg(this);
}
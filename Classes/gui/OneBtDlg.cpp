#include "OneBtDlg.h"
#include "../Constants.h"
#include "../base/Util.h"
#include <ui/UIButton.h>

OneBtDlg::OneBtDlg()
{
	auto bg = util::graphic::getSprite(Constants::ASS_BG_DLG_TEXT);
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	auto bt = ui::Button::create();
	bt->loadTextureNormal(util::graphic::getAssetName(Constants::ASS_BG_DLG_BT));
	bt->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bt->setZoomScale(1.f);
	Size size = bt->getContentSize();
	bg->setPosition(Vec2(0, size.height));	
	size.height += bt->getContentSize().height;
	bt->setPosition(Vec2(0, 0));
	this->setContentSize(size);

	util::graphic::addSwallowTouch(this);
	util::graphic::addClickBtCallback(bt, CC_CALLBACK_0(OneBtDlg::onBtClick, this));
}

void OneBtDlg::setData(const std::string& title, const std::string& closebt)
{

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
#include "SettingGUI.h"
#include "../Constants.h"
#include <ui/UICheckBox.h>
#include "../base/Util.h"
#include "../GlobalVar.h"
#include "../WordedApp.h"

SettingGUI::SettingGUI()
{
	
}

void SettingGUI::onTouchedHard(bool isTouchedHard, bool isTouchText)
{
	if (!isTouchedHard)
	{		
		auto bx = dynamic_cast<ui::CheckBox*>(getChildByTag(24));
		bool val = bx->isSelected();
		if (isTouchText)
		{
			val = !val;
			bx->setSelected(val);
		}
        GlobalVar::myData.isEnableVibration = val;
        if(val)
            util::platform::vibrate();
		util::common::saveValue(Constants::KEY_VIBRATION, Value(val));
	}
	else
	{
		auto bx = dynamic_cast<ui::CheckBox*>(getChildByTag(23));
		bool val = bx->isSelected();
		if (isTouchText)
		{
			val = !val;
			bx->setSelected(val);
		}
		WordedApp::difficult = val ? WordedApp::DIFFICULT_HARD : WordedApp::DIFFICULT_EASY;
		util::common::saveValue(Constants::KEY_HARDMODE, Value(val));
	}
}

void SettingGUI::show()
{
	Size s = this->getContentSize();
	auto cfg = Configuration::getInstance();
	this->setData(cfg->getValue("setting",Value("Settings")).asString(), cfg->getValue("close", Value("Close")).asString());
	
	Label* lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, cfg->getValue("hardMode").asString());
	lbl->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	lbl->setPositionX(220);
	lbl->setPositionY(s.height-510);
	lbl->setScale(0.7f);
	lbl->setColor(Color3B(229, 94, 72));
	addChild(lbl, 2);
	util::graphic::addNodeClickCallback(lbl, CC_CALLBACK_0(SettingGUI::onTouchedHard, this, true, true));

	ui::CheckBox* bx = ui::CheckBox::create(
		util::graphic::getAssetName(Constants::ASS_ICO_UNCHECK),
		util::graphic::getAssetName(Constants::ASS_ICO_CHECK),
		ui::Widget::TextureResType::PLIST
		);
	bx->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bx->setPosition(Vec2(110, s.height - 450));	
	bx->setTag(23);
	bx->setSelected(WordedApp::difficult == WordedApp::DIFFICULT_HARD);
	addChild(bx, 1);
	util::graphic::addClickBtCallback(bx, CC_CALLBACK_0(SettingGUI::onTouchedHard, this, true,false));

	lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, cfg->getValue("vibrate").asString());
	lbl->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	lbl->setPositionX(220);
	lbl->setPositionY(350);
	lbl->setScale(0.7f);
	lbl->setColor(Color3B(229, 94, 72));
	addChild(lbl, 2);
	util::graphic::addNodeClickCallback(lbl, CC_CALLBACK_0(SettingGUI::onTouchedHard, this, false, true));

	bx = ui::CheckBox::create(
		util::graphic::getAssetName(Constants::ASS_ICO_UNCHECK),
		util::graphic::getAssetName(Constants::ASS_ICO_CHECK),
		ui::Widget::TextureResType::PLIST
		);
	bx->setPosition(Vec2(110, 370));
	bx->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bx->setTag(24);
	bx->setSelected(GlobalVar::myData.isEnableVibration);
	addChild(bx, 1);
	util::graphic::addClickBtCallback(bx, CC_CALLBACK_0(SettingGUI::onTouchedHard, this, false,false));

	OneBtDlg::show();
}
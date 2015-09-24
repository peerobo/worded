//
//  AlertGUI.cpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/22/15.
//
//

#include "AlertGUI.h"
#include "../Constants.h"

void AlertGUI::setMsg(const std::string &msg)
{
	auto cfg = Configuration::getInstance();
	this->setData(cfg->getValue("alert", Value("Alert")).asString(), cfg->getValue("close", Value("Close")).asString());
    Label* lbl = dynamic_cast<Label*>(getChildByTag(23));
    if (!lbl) {
        Size s = this->getContentSize();
        lbl = Label::createWithBMFont(Constants::ASS_FNT_NORMAL, msg);
        lbl->setTag(23);
        addChild(lbl,2);
        lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lbl->setMaxLineWidth(s.width - 50);
        lbl->setPosition(s.width/2, s.height/2);
        lbl->setScale(0.8f);
        lbl->setColor(Color3B::BLACK);
    }
    lbl->setString(msg);
}
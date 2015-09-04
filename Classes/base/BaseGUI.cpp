//
//  BaseGUI.cpp
//  fPlay
//
//  Created by Duc_NH on 5/8/14.
//
//

#include "BaseGUI.h"

Node* BaseGUI::loadGUI(const char* fileName)
{

    auto layout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(fileName);
    this->addChild(layout);
	mGui = layout;
	initEventHandle();
	setContentSize(mGui->getContentSize());
	return mGui;
}

void BaseGUI::initEventHandle()
{

}

void BaseGUI::onDestroy()
{

}

void BaseGUI::remove()
{
    this->removeFromParent();
}

BaseGUI::~BaseGUI()
{
	destroy();
}

void BaseGUI::destroy()
{
    onDestroy();
    this->removeAllChildren();
    mGui = NULL;
    if (this->getParent() != NULL) this->removeFromParent();
}

int BaseGUI::getWidth()
{
    if (mGui != NULL) {
        return mGui->getContentSize().width * this->getScale();
    }
    return 0;
}

int BaseGUI::getHeight()
{
    if (mGui != NULL) {
		return mGui->getContentSize().height * this->getScale();
    }
    return 0;
}

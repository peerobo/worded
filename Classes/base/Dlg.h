#include <cocos2d.h>
#pragma once
USING_NS_CC;

class Dlg : public Node
{
public:
	void removeFromParent() override;
	void removeFromParentAndCleanup(bool cleanup) override;
	CREATE_FUNC(Dlg);
};
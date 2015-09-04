//
//  BaseGUI.h
//  fPlay
//
//  Created by Duc_NH on 5/8/14.
//
//

#ifndef __fPlay__BaseGUI__
#define __fPlay__BaseGUI__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "ui/UILayout.h"

using namespace cocos2d;
using namespace ui;


class BaseGUI: public Layer {
protected:
    Node* mGui;
    
    virtual void initEventHandle();
    virtual void onDestroy();
public:
	~BaseGUI();
    Node* loadGUI(const char* fileName);
    void remove();
    void destroy();
    int getWidth();
    int getHeight();

	CREATE_FUNC(BaseGUI);
};

#endif /* defined(__fPlay__BaseGUI__) */

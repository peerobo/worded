//
//  IntroScreen.h
//  1st
//
//  Created by Duc Phuong Nguyen on 9/1/15.
//
//

#include "cocos2d.h"

USING_NS_CC;

#ifndef IntroScreen_h
#define IntroScreen_h

class IntroScreen : public Layer {
    
private:
    IntroScreen();
    
    void startIntro();
public:
    CREATE_FUNC(IntroScreen);
};
#endif /* IntroScreen_h */

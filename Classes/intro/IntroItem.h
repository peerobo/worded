//
//  IntroItem.hpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/3/15.
//
//

#ifndef IntroItem_hpp
#define IntroItem_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class IntroItem : public Node{
private:
    std::function<void()> _cback;

public:
    CREATE_FUNC(IntroItem);
    
    void setValue(std::string label, std::function<void()> callback);
    void runIn(int delay);
};

#endif /* IntroItem_hpp */

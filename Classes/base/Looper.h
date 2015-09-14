//
//  Looper.h
//  1st
//
//  Created by Duc Phuong Nguyen on 9/14/15.
//
//

#ifndef Looper_h
#define Looper_h
#include <cocos2d.h>
#include <unordered_map>

USING_NS_CC;

class Looper:public Node
{
private:
    Looper();
public:
    typedef std::function<void(float)> Loopable;
    
    CREATE_FUNC(Looper);
    static Looper* instance;
    
    std::unordered_map<int, Loopable> loops;
    
    int addLoop(Loopable l);
    bool addLoop(Loopable l, int id);
    bool removeLoop(int id);
    
    void update(float dt) override;
    
};

#endif /* Looper_h */

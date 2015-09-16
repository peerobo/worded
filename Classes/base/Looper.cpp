//
//  Looper.cpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/14/15.
//
//

#include "Looper.h"

Looper* Looper::instance = NULL;

Looper::Looper()
{
    retain();
    scheduleUpdate();
    instance = this;
    loops = std::unordered_map<int,Loopable>();
}

int Looper::addLoop(Loopable l)
{
    int count = 0;
    for ( auto it = loops.begin(); it != loops.end(); ++it )
    {
        int key = it->first;
        if(key == count)
            count++;
    }
    loops[count] = l;
    return count;
}

bool Looper::addLoop(Loopable l, int id)
{
    bool checkExist = false;
    for ( auto it = loops.begin(); it != loops.end(); ++it )
    {
        int key = it->first;
        if(key == id)
            checkExist = true;
    }
    if (!checkExist) {
        loops[id] = l;
    }
    return !checkExist;
}

bool Looper::removeLoop(int id)
{
    bool del =false;
    std::unordered_map<int, Loopable>::const_iterator got = loops.find(id);
    if (got != loops.end()) {
        loops.erase(got);
        del =true;
    }
    return del;
}

void Looper::update(float dt)
{
    Node::update(dt);
    
    for ( auto it = loops.begin(); it != loops.end(); ++it )
    {
        Loopable l = it->second;
        if(l)
        {
            l(dt);
        }
    }
}

//
//  TableLogic.hpp
//  1st
//
//  Created by Duc Phuong Nguyen on 9/14/15.
//
//

#ifndef TableLogic_hpp
#define TableLogic_hpp
#include <string>
#include <vector>

class TableLogic
{
public:
    //////////////////////////////////////
    static const int LOOPER_IDX;
    bool isPlaying;
    bool isPause;
    float currTime;
    float totalTime;
    std::string word;
    std::string cat;
    std::vector<std::string> formation;
    int score;
    int level;
    float pauseTime;
    std::string answerWord;
    //////////////////////////////////////
    void loop(float dt);
    void init(const std::string& cat);
    void kill();
    void start();
    void validateState();
    void nextWord();
    void penalty();
    void endGame();
    void checkFinishCat();
};
#endif /* TableLogic_hpp */

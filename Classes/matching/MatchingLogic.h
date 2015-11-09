#pragma once
#include <string>
#include <vector> 
class MatchingLogic
{
private:
	std::vector<std::string>  catRnd;
	int catIdx;
public:
	//////////////////////////////////////
	static const int LOOPER_IDX;
	bool isPlaying;
	bool isPause;
	float currTime;
	float totalTime;	
	std::vector<std::string> formation;
	int score;
	int level;
	int remainingWord;
	float pauseTime;	
	bool isShowScore;
	std::string firstWord;
	std::string secWord;
	//////////////////////////////////////
	void loop(float dt);
	void init();
	void kill();
	void start();
	void validateState();
	void nextFormation();	
	std::string getCurrCat();
	void endGame();
};
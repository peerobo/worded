#pragma once
#include <string>
#include "Util.h"

class ScoreDB
{
private:
	ValueMap db;
public:
	static ScoreDB* instance;
	ScoreDB();

	void loadDB();
	void saveDB();

	int getScoreFor(const std::string& key);
	void setScoreFor(const std::string& key, int score);
};
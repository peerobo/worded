#include "ScoreDB.h"

ScoreDB* ScoreDB::instance = NULL;

ScoreDB::ScoreDB()
{
	instance = this;
	db = {};
}

void ScoreDB::loadDB()
{
	Value v = util::common::getValue("score");
	if (v.isNull())
		v = Value(ValueMap());
	db = v.asValueMap();
}

void ScoreDB::saveDB()
{
	util::common::saveValue("score", Value(db));
}

int ScoreDB::getScoreFor(const std::string& key)
{
	ValueMap::iterator it = db.find(key);
	if (it != db.end())
	{
		Value val = it->second;
		return val.asInt();
	}
	else
	{
		return 0;
	}
}

void ScoreDB::setScoreFor(const std::string& key, int score)
{
	db[key] = Value(score);
}
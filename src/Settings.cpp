#include "Settings.h"

USING_NS_CC;

#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadBooleanFormXML CCUserDefault::sharedUserDefault()->getBoolForKey

bool Settings::soundEnabled = true;
float Settings::screenWidth = 320;
float Settings::screenHeight = 480;
int Settings::highScores[5] = {0, 0, 0, 0, 0};

void Settings::save()
{
	SaveBooleanToXML("existed", true);
	SaveBooleanToXML("soundEnabled", soundEnabled);
	SaveIntegerToXML("score_1", highScores[0]);
	SaveIntegerToXML("score_2", highScores[1]);
	SaveIntegerToXML("score_3", highScores[2]);
	SaveIntegerToXML("score_4", highScores[3]);
	SaveIntegerToXML("score_5", highScores[4]);
}

void Settings::load()
{
	if(!LoadBooleanFormXML("existed"))
	{
		save();
	}
	else
	{
		soundEnabled = LoadBooleanFormXML("soundEnabled");
		highScores[0] = LoadIntegerFromXML("score_1");
		highScores[1] = LoadIntegerFromXML("score_2");
		highScores[2] = LoadIntegerFromXML("score_3");
		highScores[3] = LoadIntegerFromXML("score_4");
		highScores[4] = LoadIntegerFromXML("score_5");
	}
}
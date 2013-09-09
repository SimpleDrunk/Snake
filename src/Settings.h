#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"

class Settings
{
public:
	static bool soundEnabled;
	static float screenWidth;
	static float screenHeight;
	static int highScores[5];

	static void load();
	static void save();
};

#endif
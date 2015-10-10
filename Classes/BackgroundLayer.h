#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
	CREATE_FUNC(BackgroundLayer);
	bool init();
	void createBackground(std::string filename);
	float getSpeed();
	void setSpeed(float speed);
	void update(float dt);

	Sprite* bg;
	Sprite* tempBg;
	float speed;
	float bgWidth;
	Size visibleSize;
	Point origin;
};
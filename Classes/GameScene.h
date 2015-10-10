#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "BackgroundLayer.h"
#include "PlayerLayer.h"
#include "ObstacleLayer.h"
#include "ControlLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
	void runObstacle();
	void setSpeed(float speed);
	void setEffect(bool effect);
	void Gameover();
	void update(float dt);
	
	BackgroundLayer* bg;
	PlayerLayer* player;
	ObstacleLayer* obstacle;
	ControlLayer* control;
	Sprite* scoreLable;
	Sprite* gameover;
	float i;
	int score;
	bool loseFlag;
	bool effectFlag;
	bool overFlag;
	Size visibleSize;
	Point origin;
};
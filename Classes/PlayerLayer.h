#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class PlayerLayer : public Layer
{
public:
	CREATE_FUNC(PlayerLayer);
	bool init();
	void onEnter();
	void upwardAnimate();
	void downwardAnimate();
	void createPlayer(std::string filename);
	Point getPlayerPosition();
	void update(float dt);
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	Sprite* player;
	int playerUpwardFrameNum;
	float playerUpwardAnimateSpeed;
	int playerDownwardFrameNum;
	bool upFlag;
	float playerDownwardAnimateSpeed;
	float y;
	float acceleration;
	float velocity;
	float gravity;
	float upwarda;
	float dowarda;
	Size visibleSize;
	Point origin;
};
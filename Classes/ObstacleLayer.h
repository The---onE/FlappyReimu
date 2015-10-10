#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class ObstacleLayer : public Layer
{
public:
	CREATE_FUNC(ObstacleLayer);
	bool init();
	void createObstacle(std::string filename_u, std::string filename_d, float y);
	void randomObstacle();
	float getSpeed();
	void setSpeed(float speed);
	bool checkCollision(Point p);
	void update(float dt);

	std::shared_ptr<Vector<Sprite*>> obstacleArray;
	float speed;
	float hitRectX;
	float hitRectY;
	Size visibleSize;
	Point origin;
};


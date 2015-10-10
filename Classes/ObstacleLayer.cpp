#include "ObstacleLayer.h"

bool ObstacleLayer::init()
{
	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	obstacleArray = std::make_shared<Vector<Sprite*>>();

	hitRectX = visibleSize.height*0.0024;
	hitRectY = visibleSize.height*0.0039;
	speed = 2;

	scheduleUpdate();
	return true;
}

void ObstacleLayer::createObstacle(std::string filename_u, std::string filename_d, float y)
{
	Sprite* obstacle_u;
	obstacle_u = Sprite::createWithSpriteFrameName(filename_u);
	SETSIZE(obstacle_u, 0.9);
	obstacle_u->setAnchorPoint(Point::ZERO);
	obstacle_u->setPosition(Point(origin.x + visibleSize.width, origin.y + y + visibleSize.height*0.10));
	obstacleArray->pushBack(obstacle_u);
	addChild(obstacle_u);
	Sprite* obstacle_d;
	obstacle_d = Sprite::createWithSpriteFrameName(filename_d);
	SETSIZE(obstacle_d, 0.9);
	obstacle_d->setAnchorPoint(Point(0, 1));
	obstacle_d->setPosition(Point(origin.x + visibleSize.width, origin.y + y - visibleSize.height*0.10));
	obstacleArray->pushBack(obstacle_d);
	addChild(obstacle_d);
}

void ObstacleLayer::randomObstacle()
{
	float temp = (int)rand() % 600 + 200;
	float y = visibleSize.height * (temp / 1000) ;
	this->createObstacle("o_u.png", "o_d.png", y);
}

float ObstacleLayer::getSpeed()
{
	return speed;
}
void ObstacleLayer::setSpeed(float speed)
{
	this->speed = speed;
}

bool ObstacleLayer::checkCollision(Point p)
{
	Rect playerRect = Rect(p.x - hitRectX/2, p.y - hitRectY/2, hitRectX, hitRectY);
	for (int i=obstacleArray->size()-1; i>=0; --i)
	{
		Sprite* obstacle = (Sprite*)obstacleArray->at(i);
		Rect obRect = obstacle->getBoundingBox();
		if (obRect.intersectsRect(playerRect))
		{
			return true;
		}
	}
	return false;
}

void ObstacleLayer::update(float dt)
{
	for (int i=obstacleArray->size()-1; i>=0; --i)
	{
		Sprite* obstacle = (Sprite*)obstacleArray->at(i);
		float x = obstacle->getPositionX();
		if (x < -obstacle->getContentSize().width * obstacle->getScaleY())
		{
			obstacleArray->eraseObject(obstacle);
			this->removeChild(obstacle);
		}
		else
		{
			obstacle->setPositionX(x - speed);
		}
	}
}
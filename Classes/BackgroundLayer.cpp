#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	createBackground("sprites/bg.png");

	scheduleUpdate();
	return true;
}

void BackgroundLayer::createBackground(std::string filename)
{
	bg = Sprite::create(filename);
	bg->setAnchorPoint(Point::ZERO);
	SETSIZE(bg, 1);
	bg->setPosition(Point::ZERO);
	this->addChild(bg);

	tempBg = Sprite::create(filename);
	tempBg->setAnchorPoint(Point(1, 0));
	SETSIZE(tempBg, 1);
	tempBg->setPosition(Point(visibleSize.width, 0));
	tempBg->setVisible(false);
	this->addChild(tempBg, 0);

	bgWidth = bg->getContentSize().width * bg->getScaleY();
}

float BackgroundLayer::getSpeed()
{
	return speed;
}
void BackgroundLayer::setSpeed(float speed)
{
	this->speed = speed;
}

void BackgroundLayer::update(float dt)
{
	float x = bg->getPositionX() - speed;
	float y = bg->getPositionY();
	if (x < visibleSize.width - bgWidth)
	{
		x = visibleSize.width;
		tempBg->setVisible(true);
		tempBg->setPosition(Point(x, 0));
	}
	bg->setPosition(Point(x, y));
	if (tempBg->isVisible())
	{
		if (x < 0)
		{
			tempBg->setVisible(false);
		}
		tempBg->setPosition(Point(x, y));
	}
}
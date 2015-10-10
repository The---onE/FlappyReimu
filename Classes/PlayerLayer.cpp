#include "PlayerLayer.h"

bool PlayerLayer::init()
{
#define STAND_ANIMATE 1
#define UPWARD_ANIMATE 2
#define DOWNWARD_ANIMATE 3
	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	upFlag = false;
	y = 0.5;
	velocity = 0;
	gravity = -1;
	upwarda = 2;
	dowarda = -3;
	acceleration = gravity;
	playerUpwardFrameNum = 5;
	playerUpwardAnimateSpeed = 0.15f;
	playerDownwardFrameNum = 5;
	playerDownwardAnimateSpeed = 0.15f;
	createPlayer("p_0/p_0.png");

	scheduleUpdate();
	return true;
}

void PlayerLayer::onEnter()
{
	Layer::onEnter();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(PlayerLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void PlayerLayer::createPlayer(std::string filename)
{
	player = Sprite::createWithSpriteFrameName(filename);
	downwardAnimate();
	SETSIZE(player, 0.075);
	player->setPosition(Point(origin.x + 0.2*visibleSize.width, origin.y + y*visibleSize.height));
	addChild(player);
}

void PlayerLayer::upwardAnimate()
{
	player->stopActionByTag(STAND_ANIMATE);
	player->stopActionByTag(UPWARD_ANIMATE);
	player->stopActionByTag(DOWNWARD_ANIMATE);
	Animation *playerAnimate = Animation::create();
	for (int i=0; i<playerUpwardFrameNum; i++)
	{
		char name[32];
		sprintf(name, "p_0/p_0_1/p_0_1_%d.png", i);
		playerAnimate->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	playerAnimate->setDelayPerUnit(playerUpwardAnimateSpeed);
	RepeatForever* animate = RepeatForever::create(Animate::create(playerAnimate));
	animate->setTag(UPWARD_ANIMATE);
	player->runAction(animate);
}

void PlayerLayer::downwardAnimate()
{
	player->stopActionByTag(STAND_ANIMATE);
	player->stopActionByTag(UPWARD_ANIMATE);
	player->stopActionByTag(DOWNWARD_ANIMATE);
	Animation *playerAnimate = Animation::create();
	for (int i=0; i<playerDownwardFrameNum; i++)
	{
		char name[32];
		sprintf(name, "p_0/p_0_2/p_0_2_%d.png", i);
		playerAnimate->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	playerAnimate->setDelayPerUnit(playerDownwardAnimateSpeed);
	RepeatForever* animate = RepeatForever::create(Animate::create(playerAnimate));
	animate->setTag(DOWNWARD_ANIMATE);
	player->runAction(animate);
}

Point PlayerLayer::getPlayerPosition()
{
	return player->getPosition();
}

void PlayerLayer::update(float dt)
{
	if (velocity > 0)
	{
		if (acceleration < 0)
			acceleration = dowarda;
	}
	else if (velocity < 0)
	{
		if (acceleration < 0)
			acceleration = gravity;
	}

	y += velocity*dt + 1/2*acceleration*dt*dt;
	velocity += acceleration * dt;
	player->setPositionY(y * visibleSize.height);

	Point position = player->getPosition();
	if (position.x < 0)
	{
		player->setPositionX(0);
	}
	else if (position.x >visibleSize.width)
	{
		player->setPositionX(visibleSize.width);
	}
	if (position.y < 0)
	{
		player->setPositionY(0);
		y = 0;
		velocity = 0;
	}
	else if (position.y > visibleSize.height)
	{
		player->setPositionY(visibleSize.height);
		y = 1;
		velocity = 0;
	}
}

bool PlayerLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!upFlag)
	{
		upwardAnimate();
		acceleration = upwarda;
		upFlag = true;
		return true;
	}
	return false;
}

void PlayerLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (upFlag)
	{
		downwardAnimate();
		acceleration = gravity;
		upFlag = false;
	}
}
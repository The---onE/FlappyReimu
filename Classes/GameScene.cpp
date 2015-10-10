#include "GameScene.h"
#include "MainScene.h"

bool GameScene::init()
{
	Scene::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	srand(time(NULL));

	bg = BackgroundLayer::create();
	addChild(bg, 0);
	player = PlayerLayer::create();
	addChild(player, 50);
	obstacle = ObstacleLayer::create();
	addChild(obstacle, 100);
	control = ControlLayer::create();
	addChild(control, 1000);

	loseFlag = false;
	overFlag = false;
	effectFlag = false;
	setSpeed(2.5);
	i = 0;
	score = 0;

	runObstacle();
	scheduleUpdate();
	return true;
}

void GameScene::runObstacle()
{
	obstacle->randomObstacle();
}

void GameScene::setSpeed(float speed)
{
	bg->setSpeed(speed);
	obstacle->setSpeed(speed);
}

void GameScene::setEffect(bool effect)
{
	effectFlag = effect;
}

void GameScene::Gameover()
{
	char text[32];
	sprintf(text, "GAME OVER\nscore:%d", score);
	gameover = LabelTTF::create(text, "Arial", 50, Size(visibleSize.width, visibleSize.height),TextHAlignment::CENTER,TextVAlignment::CENTER);
	gameover->setPosition(Point(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height*0.5));
	gameover->setScale(0.5);
	addChild(gameover, 1000);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}

void GameScene::update(float dt)
{
	float speed = bg->getSpeed();
	setSpeed(speed + 0.001);

	i += 1;
	if (i > 120 - speed*8)
	{
		runObstacle();
		i = 0;
	}
	score++;
	
	if (obstacle->checkCollision(player->getPlayerPosition()))
	{
		if (!loseFlag)
		{
			Gameover();
			loseFlag = true;
			if (effectFlag)
				SimpleAudioEngine::getInstance()->playEffect("musics/hurt.wav");
		}
	}

	if (loseFlag && !overFlag)
	{
		float rotateG = gameover->getRotation();
		float scaleG = gameover->getScale();
		gameover->setRotation(rotateG + 24);
		gameover->setScale(scaleG + 0.02);
		if (gameover->getScale()>1.5 && (int)(gameover->getRotation())%360<24)
			overFlag = true;
	}

	removeChild(scoreLable);
	char text[32];
	sprintf(text, "score:%d", score);
	scoreLable = LabelTTF::create(text, "Arial", 24);
	scoreLable->setPosition(Point(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height*0.9));
	addChild(scoreLable,500);
}
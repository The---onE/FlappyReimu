#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

class ControlLayer : public Layer
{
public:
	CREATE_FUNC(ControlLayer);

protected:
	bool init();
	void onEnter();
	void createCloseButton(std::string filenameN, std::string filenameS);
	void createPauseButton(std::string filenameN, std::string filenameS);
	void createRestartButton(std::string filenameN, std::string filenameS);
	void quitGame();
	void pauseGame();
	void restartGame();
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	bool pauseFlag;
	Size visibleSize;
	Point origin;
};


#include "AppDelegate.h"
#include "MainScene.h"
#include "GameScene.h"

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/item.plist", "sprites/item.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/player.plist", "sprites/player.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/obstacle.plist", "sprites/obstacle.png");

	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("musics/bgm.mp3");
	audio->preloadEffect("musics/hurt.wav");

	Scene* scene = MainScene::create();
	director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

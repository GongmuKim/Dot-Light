#include "AppDelegate.h"
#include "GameScene.h"
#include "GameMenuScene.h"
#include "TitleScene.h"
#include "loading.h"
#include "data.h"
USING_NS_CC;
CocosDenshion::SimpleAudioEngine *sound=CocosDenshion::SimpleAudioEngine::sharedEngine();
int stage=1,max_stage,stage_star[20][5];
Datas *data=new Datas();

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		//1440 2560 / 1080 1920 / 720 1280 / 540 960 ->432 768    9:16
		//640 1136->320 568    40:71 거의안잘림
		//640 960->320 480     2:3  세로확잘림
		//480 800->360 600     3:5  세로꽤잘림
		//800 1280->400 640     5:8  
		//? 가로잘림 임시
		Rect rects[10];
		rects[0].setRect(0,0,768,432);
		rects[1].setRect(0,0,568,320);
		rects[2].setRect(0,0,480*1.5,320*1.5);
		rects[3].setRect(0,0,600,360);
		rects[4].setRect(0,0,640,400);
		rects[5].setRect(0,0,800,432);
		glview = GLView::createWithRect("My Game",rects[0]);
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = Loading::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

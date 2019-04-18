#include "AppDelegate.h"
#include "GameScene.h"
#include "GameMenuScene.h"
#include "TitleScene.h"
#include "loading.h"
#include "data.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;



CocosDenshion::SimpleAudioEngine *sound=CocosDenshion::SimpleAudioEngine::sharedEngine();
int stage=1,max_stage,stage_star[20][5];
Datas *datas=new Datas();



static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 1920);
static cocos2d::Size smallResolutionSize = cocos2d::Size(320, 480);//3:2
static cocos2d::Size mediumResolutionSize = cocos2d::Size(768, 1024);//4:3   16 12  16 9
static cocos2d::Size largeResolutionSize = cocos2d::Size(1536, 2048);//4:3   16 12  16 9   1536 2048
static cocos2d::Size ggResolutionSize = cocos2d::Size(1080, 1920);//가로잘리는거

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		Rect rects[10];
		rects[0].setRect(0, 0, 768, 432);
		rects[1].setRect(0, 0, 568, 320);
		rects[2].setRect(0, 0, 480 * 1.5, 320 * 1.5);
		rects[3].setRect(0, 0, 600, 360);
		rects[4].setRect(0, 0, 640, 400);
		rects[5].setRect(0, 0, 800, 432);


		glview = GLViewImpl::createWithRect("ims", Rect(0, 0, 1080,1920));
		glview->setFrameSize(1920,1080);//컴에서 화면크기
		glview->setFrameZoomFactor(0.7f);
#else
		glview = GLViewImpl::create("ims");
#endif
		director->setOpenGLView(glview);
	}

	Size frameSize = glview->getFrameSize();

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(1920,1080, ResolutionPolicy::SHOW_ALL);
	//double t = frameSize.width;
	//frameSize.width = frameSize.height;
	//frameSize.height = t;
	// if the frame's height is larger than the height of medium size.

	/*
	if (frameSize.height > mediumResolutionSize.height)
	{
	director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
	}
	// if the frame's height is larger than the height of small size.
	else if (frameSize.height > smallResolutionSize.height)
	{
	director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
	}
	// if the frame's height is smaller than the height of medium size.
	else
	{
	director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
	}
	*/
	register_all_packages();

	// create a scene. it's an autorelease object
	//auto scene = GameScene::createScene();
	//auto scene = HelloWorld::createScene();
	auto scene = Loading::createScene();
	//auto scene = HelloWorld::createScene();

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

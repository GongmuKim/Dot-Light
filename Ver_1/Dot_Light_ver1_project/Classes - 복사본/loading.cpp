#include "loading.h"
#include "TitleScene.h"
#include "data.h"

USING_NS_CC;

extern int stage,max_stage,stage_star[20][5];
extern CocosDenshion::SimpleAudioEngine *sound;
extern Datas *data;

Scene* Loading::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Loading::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Loading::init()
{
	sound->playBackgroundMusic("sound/bg.wav",true);
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
  

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    label = LabelTTF::create("0.00%", "Arial",77);
	label->setColor(Color3B::BLACK);
    
    // position the label on the center of the screen
	label->setPosition(Director::sharedDirector()->getWinSize()/2.0);

    // add the label as a child to this layer
    this->addChild(label, 1);
    
	
	GB2ShapeCache::getInstance()->addShapesWithFile("map/map.plist");
	GB2ShapeCache::getInstance()->addShapesWithFile("map/j.plist");
	GB2ShapeCache::getInstance()->addShapesWithFile("map/maps.plist");

		char name[200]={0};

		if(CCUserDefault::sharedUserDefault()->getStringForKey("first").empty()){
		CCUserDefault::sharedUserDefault()->setStringForKey("first","FIRST");
		CCUserDefault::sharedUserDefault()->setBoolForKey("bg",true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("ef",true);


		data->set_max_stage(1);
		//UserDefault::sharedUserDefault()->setIntegerForKey("openstage",1);
		for(int i=1;i<=10;i++){
			for(int j=1;j<=3;j++){
				sprintf(name,"stage%dstar%d",i,j);
				UserDefault::sharedUserDefault()->setIntegerForKey(name,0);
				//stage_star[i][j]=0;
			}
		}
	}

		max_stage=UserDefault::sharedUserDefault()->getIntegerForKey("openstage");
		
		sound->setBackgroundMusicVolume(UserDefault::sharedUserDefault()->getBoolForKey("bg"));
		sound->setEffectsVolume(UserDefault::sharedUserDefault()->getBoolForKey("ef"));
		for(int i=1;i<=10;i++){
			for(int j=1;j<=3;j++){
				//sprintf(name,"stage%dstar%d",i,j);
				//stage_star[i][j]=UserDefault::sharedUserDefault()->getIntegerForKey(name);
				stage_star[i][j]=data->get_stage_star(i,j);
			}
		}
		
		auto sp=Sprite::create("player.png");
		sp->setPosition(Director::sharedDirector()->getWinSize()/2.0);
		this->addChild(sp);
		sp->setName("sp");
		sp->setScale(0);

		



		image_cnt=65;//전체그림숫자
		himage_cnt=0;
		//뺀거:closenormal,closeselected,colorramp,del,hello,hello2,
	Director::getInstance()->getTextureCache()->addImageAsync("ball.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("bg2.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("black_bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("btn.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("control.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("end.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("end_bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("enemy.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("joystick.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("joystick_bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("light.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("line.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("mirror.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("player.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("playerd.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("star_bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("star1.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("star2.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/1.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/2.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/3.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/4.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/5.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/6.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/7.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/8.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/9.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/10.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/1j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/2j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/3j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/4j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/5j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/6j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/7j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/8j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/9j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("map/10j.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/bgm.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/bgm_bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/bgms.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/btn.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/btn_bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/btn_lock.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/btn_s.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/ef.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/efs.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/font_s.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/soundx.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("menu/soundxs.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/bbg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/bg.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/btn.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/btn_s.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/clear.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/exit.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/gameover.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/menu.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/next.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/pause.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/restart.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/x.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/x_btn.png",CC_CALLBACK_1(Loading::callback,this));
	Director::getInstance()->getTextureCache()->addImageAsync("popup/x_s.png",CC_CALLBACK_1(Loading::callback,this));
	
    return true;
}


void Loading::callback(Texture2D *tex)
{
	himage_cnt++;
	double gap=(double)himage_cnt/(double)image_cnt;
	((Sprite*)this->getChildByName("sp"))->setScale( gap*gap*gap *130.0);
	char name[200]={0};
	sprintf(name,"Loading:%.1lf",(double)(himage_cnt+1)/(double)(image_cnt)*100);
	name[strlen(name)]='%';
	label->setString(name);
	
	if(himage_cnt==image_cnt){
		Director::sharedDirector()->replaceScene(TitleScene::createScene());
	}
}

void Loading::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

	Director::getInstance()->replaceScene(TitleScene::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

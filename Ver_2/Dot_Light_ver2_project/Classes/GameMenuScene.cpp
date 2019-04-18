#include "GameMenuScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "data.h"
USING_NS_CC;

extern int stage,max_stage,stage_star[20][5];
extern CocosDenshion::SimpleAudioEngine *sound;
extern Datas *datas;

Scene* GameMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//sound->setEffectsVolume(0);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	winSize=Director::getInstance()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "popup/btn.png",
                                           "popup/btn_s.png",
                                           CC_CALLBACK_1(GameMenuScene::menuCloseCallback, this));
    
	closeItem->setPosition(ccp(closeItem->getContentSize().width/2.0+50,winSize.height-(closeItem->getContentSize().height/2.0+50)));
	closeItem->setTag(0);

	auto bgm_btn=MenuItemToggle::createWithTarget(this,menu_selector(GameMenuScene::menuCloseCallback),MenuItemImage::create("menu/bgm.png","menu/bgms.png"),MenuItemImage::create("menu/soundx.png","menu/soundxs.png"),NULL);
	bgm_btn->setPosition(ccp(winSize.width-(bgm_btn->getContentSize().width/2.0+50),winSize.height-(bgm_btn->getContentSize().height/2.0+50)));
	bgm_btn->setTag(1);
	if(sound->getBackgroundMusicVolume()<0.5) bgm_btn->setSelectedIndex(1);

	auto ef_btn=MenuItemToggle::createWithTarget(this,menu_selector(GameMenuScene::menuCloseCallback),MenuItemImage::create("menu/ef.png","menu/efs.png"),MenuItemImage::create("menu/soundx.png","menu/soundxs.png"),NULL);
	ef_btn->setPosition(ccp(winSize.width-(ef_btn->getContentSize().width*1.5+50),winSize.height-(ef_btn->getContentSize().height/2.0+50)));
	ef_btn->setTag(2);
	if(sound->getEffectsVolume()<0.5) ef_btn->setSelectedIndex(1);
	

	Sprite* btnbg=Sprite::create("popup/next.png");
	btnbg->setPosition(closeItem->getPosition());
	btnbg->setRotation(180);
	this->addChild(btnbg);
	btnbg->setScale(0.7);
	closeItem->setScale(0.7);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,bgm_btn,ef_btn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    /*
    label = LabelTTF::create("Hello World", "Arial", 24);
	if(sound->getBackgroundMusicVolume()<0.5){
		label->setString("bg_off");
	}
	label->setVisible(false);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
	label->setScale(2);

    // add the label as a child to this layer
    this->addChild(label, 1);*/

    // add "GameMenuScene" splash screen"
    auto sprite = Sprite::create("menu/stage.png");

    // position the sprite on the center of the screen
	sprite->setPosition(ccp(winSize.width/2,930));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(GameMenuScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
	

	char name[200]={0};


	Menu* menus=Menu::create(NULL);
	menus->setPosition(ccp(0,0));
	this->addChild(menus,3);
	for(int i=1;i<=5;i++){//0 1   2 3  2 1
		auto menu_bg=Sprite::create("menu/btn_bg.png");
		//menu_bg->setPosition(ccp(winSize.width/6.0*((i-1)%5  +1),winSize.height/3.0* (((i-1)/5 +3)%2+1)   -100        ) );
		menu_bg->setPosition(ccp(winSize.width / 6.0*((i - 1) % 5 + 1), winSize.height / 2.0));
		this->addChild(menu_bg,0);


		auto menu_item=MenuItemImage::create("menu/btn.png","menu/btn_s.png","menu/btn_lock.png",CC_CALLBACK_1(GameMenuScene::select_stage, this));
		//auto menu_item=MenuItemSprite::create(menu_sp,nullptr,menu_sp,CC_CALLBACK_1(GameMenuScene::select_stage, this));
		menu_item->setPosition(ccp(winSize.width/6.0*((i-1)%5  +1),winSize.height/2.0 ) );
		menu_item->setTag(i);
		menus->addChild(menu_item,3);
		if(i>max_stage) menu_item->setEnabled(false);
		
		sprintf(name,"%d",i);
		LabelAtlas *stage_font=LabelAtlas::create(name,"menu/font_s.png",120,200,'0');
		stage_font->setPosition(menu_bg->getPosition());
		stage_font->setAnchorPoint(ccp(0.5,0.5));
		this->addChild(stage_font,2);

		for(int j=1;j<=3;j++)
		{
			Sprite* spr;
			if(stage_star[i][j]==1) spr=Sprite::create("star1.png");
			else spr=Sprite::create("star_bg.png");
			Point menu_pos=menu_item->getPosition();
			spr->setPosition(ccp(menu_pos.x+(j-2)*80,menu_pos.y-100));
			spr->setScale(0.5);
			this->addChild(spr,2);
		}
	}
    
    return true;
}


void GameMenuScene::menuCloseCallback(Ref* pSender)
{
	Node* node = (Node*) pSender;	
	int tag=node->getTag();
	if(tag==0)Director::sharedDirector()->replaceScene(TitleScene::createScene());
	else if(tag==1){
		sound->setBackgroundMusicVolume((sound->getBackgroundMusicVolume()-1.0)*-1.0);
		UserDefault::sharedUserDefault()->setBoolForKey("bg",sound->getBackgroundMusicVolume());
	}
	else if(tag==2){
		sound->setEffectsVolume((sound->getEffectsVolume()-1.0)*-1.0);
		UserDefault::sharedUserDefault()->setBoolForKey("ef",sound->getEffectsVolume());
	}
}

void GameMenuScene::select_stage(Ref* pSender){
	Node* node = (Node*) pSender;	
	int tag=node->getTag();
	/*
	char name[200]={0};
	sprintf(name,"stage:%d",tag);
	label->setString(name);*/

	stage=tag;
	//Director::sharedDirector()->replaceScene(TransitionFadeTR::create(1,GameScene::createScene()));
	auto black_sp=Sprite::create("black_bg.png");
	black_sp->setPosition(winSize/2);
	black_sp->setOpacity(0);
	this->addChild(black_sp,100);
	
	auto act=CallFunc::create(this,callfunc_selector(GameMenuScene::go_scene));
	auto seq=Sequence::create(FadeIn::create(0.5),DelayTime::create(0.2),act,NULL);
	black_sp->runAction(seq);

}
void GameMenuScene::go_scene()
{
	Director::sharedDirector()->replaceScene(GameScene::createScene());
}

void GameMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::sharedDirector()->replaceScene(TitleScene::createScene());
	}
}
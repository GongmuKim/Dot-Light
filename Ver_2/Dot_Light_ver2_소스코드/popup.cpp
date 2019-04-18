#include "Popup.h"
#include "GameScene.h"
extern CocosDenshion::SimpleAudioEngine *sound;
extern int stage;

using namespace cocos2d;


Popup::Popup(int state)
{
	this->state=state;//일시정지 클리어 죽음
	CCString* popParam=CCString::create("0");
	//CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기

	winSize=CCDirector::sharedDirector()->getWinSize();
	
	auto sprite=Sprite::create("popup/bg.png");
	sprite->setPosition(ccp(0,0));
	//sprite->setOpacity(125.0f);
	this->addChild(sprite,1);

	//메뉴추가
	
	MenuItemImage* menu=MenuItemImage::create("popup/btn.png","popup/btn_s.png",CC_CALLBACK_1(Popup::do_btn, this));
	menu->setPosition(-250,0);
	menu->setTag(0);

	MenuItemImage* restart=MenuItemImage::create("popup/btn.png","popup/btn_s.png",CC_CALLBACK_1(Popup::do_btn, this));
	restart->setPosition(0,0);
	restart->setTag(1);

	//MenuItemImage* exit=MenuItemImage::create("popup/btn.png","popup/btn_s.png",CC_CALLBACK_1(Popup::do_btn, this));
	//exit->setPosition(250,0);
	//exit->setTag(2);

	MenuItemImage* next=MenuItemImage::create("popup/btn.png","popup/btn_s.png",CC_CALLBACK_1(Popup::do_btn, this));
	next->setPosition(250,0);
	next->setTag(3);

	MenuItemImage* xbtn=MenuItemImage::create("popup/x_btn.png","popup/x_s.png",CC_CALLBACK_1(Popup::do_btn, this));
	xbtn->setPosition(ccp(500,800));
	xbtn->setTag(4);

	xbtn->setName("X");


	auto bgm_btn=MenuItemToggle::createWithTarget(this,menu_selector(Popup::do_btn),MenuItemImage::create("menu/bgm.png","menu/bgms.png"),MenuItemImage::create("menu/soundx.png","menu/soundxs.png"),NULL);
	bgm_btn->setPosition(ccp(-200,200));
	bgm_btn->setTag(100);
	if(sound->getBackgroundMusicVolume()<0.5) bgm_btn->setSelectedIndex(1);

	auto ef_btn=MenuItemToggle::createWithTarget(this,menu_selector(Popup::do_btn),MenuItemImage::create("menu/ef.png","menu/efs.png"),MenuItemImage::create("menu/soundx.png","menu/soundxs.png"),NULL);
	ef_btn->setPosition(ccp(200,200));
	ef_btn->setTag(200);
	if(sound->getEffectsVolume()<0.5) ef_btn->setSelectedIndex(1);;


	//일시정지 클리어 죽음
	if(state==1){
		menus=Menu::create(menu,restart, NULL);
		menus->alignItemsHorizontallyWithPadding(300);
		menus->addChild(xbtn);
		this->add_sprite(menu->getPosition(),"popup/menu.png");
		this->add_sprite(restart->getPosition(),"popup/restart.png");
		this->add_sprite(xbtn->getPosition(),"popup/x.png");
		this->add_sprite(ccp(0,530),"popup/pause.png");
		menus->addChild(bgm_btn);
		menus->addChild(ef_btn);

	}
	else if(state==2){
		menus=Menu::create(menu,restart, NULL);
		if (stage < 5) {
			menus->addChild(next);
			menus->alignItemsHorizontallyWithPadding(100);
			this->add_sprite(next->getPosition(), "popup/next.png");
		}
		else {
			menus->alignItemsHorizontallyWithPadding(300);
		}
		this->add_sprite(menu->getPosition(),"popup/menu.png");
		this->add_sprite(restart->getPosition(),"popup/restart.png");
		//this->add_sprite(exit->getPosition(),"popup/exit.png");
		this->add_sprite(ccp(0,530),"popup/clear.png");
	}
	else if(state==3){
		menus=Menu::create(menu,restart, NULL);
		menus->alignItemsHorizontallyWithPadding(300);
		this->add_sprite(menu->getPosition(),"popup/menu.png");
		this->add_sprite(restart->getPosition(),"popup/restart.png");
		//this->add_sprite(exit->getPosition(),"popup/exit.png");
		this->add_sprite(ccp(0,470),"popup/gameover.png");
	}
	menus->setPosition(ccp(0,-400));
	this->addChild(menus,10);


}




void Popup::do_btn(Ref* pSender)
{	
	//CCLog("popup_bnt_click");
	Node* node = (Node*) pSender;	
	int tag=node->getTag();
	char name[200]={0};
	sprintf(name,"%d",tag);
	CCString* popParam=CCString::create(name);

	if(tag>99){
		if(tag==100) {
			sound->setBackgroundMusicVolume((sound->getBackgroundMusicVolume()-1.0)*-1.0);
		UserDefault::sharedUserDefault()->setBoolForKey("bg",sound->getBackgroundMusicVolume());
		}
		else if(tag==200) {
		sound->setEffectsVolume((sound->getEffectsVolume()-1.0)*-1.0);
		UserDefault::sharedUserDefault()->setBoolForKey("ef",sound->getEffectsVolume());
		}
		return;
	}
	//CCLog("post tag");
	if(tag==0)CCNotificationCenter::sharedNotificationCenter()->postNotification("menu", pSender);         //노티피케이션 보내기
	else if(tag==1)CCNotificationCenter::sharedNotificationCenter()->postNotification("restart", pSender);         //노티피케이션 보내기
	else if(tag==2)CCNotificationCenter::sharedNotificationCenter()->postNotification("exit", pSender);         //노티피케이션 보내기
	else if(tag==3) CCNotificationCenter::sharedNotificationCenter()->postNotification("next", pSender);
	else CCNotificationCenter::sharedNotificationCenter()->postNotification("resume", pSender);
	//CCLog("end post tag");
	


	//팝업창 제거
	this->removeFromParentAndCleanup(true);
	//CCLog("delete_popup");
}

void Popup::add_sprite(Point pos,char sp_name[])
{
	auto sp1=Sprite::create(sp_name);
	sp1->setPosition(ccp(pos.x,pos.y-400));
	this->addChild(sp1,2);
}

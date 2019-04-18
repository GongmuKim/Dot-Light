#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class Popup : public cocos2d::CCLayer
{
public:
    //virtual bool init();
    //static cocos2d::CCScene* scene();    
    //CREATE_FUNC(Popup);
	
	cocos2d::CCSize winSize;

	Popup(int state);

	
	CCLayerColor* backLayer;
	CCLayerColor* popUpLayer;

	Menu* menus;
	
	void do_btn(Ref* pSender);
	void add_sprite(Point pos,char sp_name[]);
private:
	int state;
};
#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void select_stage(Ref* pSender);
	void go_scene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMenuScene);
private:
	Size winSize;
	//LabelTTF *label;
};

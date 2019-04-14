#pragma once

#include "cocos2d.h"
#include "GB2ShapeCache-x.h"
USING_NS_CC;

class Loading : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void callback(Texture2D *texture);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Loading);
private:
	int himage_cnt,image_cnt;
	LabelTTF *label;
};

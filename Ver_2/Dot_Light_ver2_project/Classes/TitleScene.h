#pragma once

#include "cocos2d.h"
#include "mymath.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class TitleScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


	void shader_test();
	GLProgramState *start_shader(Sprite *sprite);
	GLProgramState *start_shader(MenuItemImage *sprite);
	void set_gl_state(GLProgramState *st, bool off);
	void update_gl_state(float dt);
	 virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event);

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
private:
	Size winSize;
	Point end;
	GLProgramState *btn_st,*bg_st;
	Mymath *mymath;
	Point ims_t;
	int iscontrol;
	double start_angle,bh_angle,before_angle,before_rangle,r_angle;

	double movetime;
	double movebh;
};
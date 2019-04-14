#pragma once

#include "cocos2d.h"
#include"Box2D/Box2D.h"
#include "GB2ShapeCache-x.h"
#include "enemy.h"
#include "mymath.h"
#include "myray.h"
#include "CCGL.h"
#include <List>
USING_NS_CC;
using namespace std;
class GameScene : public cocos2d::Layer, public b2ContactListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    void update(float dt);
	void update_enemy(float dt);
	void update_box2d(float dt);
	void update_gl_state(float dt);
	void update_line(float dt);
	void set_touch();

	virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);


	void set_gl_state(GLProgramState* st,bool on);
	
    // implement the "static create()" method manually
	 virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event);

	 virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	b2Body* addc(Point pos,char sp_anme[], double rad);

	void set_world();
	void create_player();
	void create_enemy();
	void create_controler();
	void addmap();
	void addj();
	void set_data();
	void clear();
	void popup_open(Node *sender);
	void die();
	void draw_light(Point pos,double len);


	void star_effect();
	~GameScene();


	void shader_test();
	GLProgramState* start_shader(Sprite *sp);

	virtual void draw(Renderer* renderer, const kmMat4& transform, uint32_t transformUpdated);




	
	void domenus(Object *obj);

    CREATE_FUNC(GameScene);
private:
	Size winSize,visibleSize,origin;
	bool isfind;//,isbg;
	int isjoystick, iscontrol;
	double r_angle,before_rangle,before_angle;
	//LabelTTF *label;

	b2World *world;
	b2Body* player;
	Point joystick_g,joystick_h, ims_rend2,normalp;
	Sprite *joystick,*joystick_bg,*light,*light2;
	Sprite *control_angle, *st_angle;
	double start_angle,bh_angle;
	int raycast_index;
	int ref;
	list<enemy*> enemy_list;
	Sprite *line1, *line2;
	Mymath *mymath;
	Myray *rend1,*rend2;
	Myray *end_ray1[370];
	ClippingNode *clip_light;
	DrawNode *shape_light;

	Point start_pos[15],end_pos[15],enemy_pos[15][10],mirror_pos[15],star_pos[15][5];
	int enemy_cnt[15],enemy_speed[15][10];
	bool get_mirror,get_stars[5];

	GLProgramState *st_mirror, *st_star[5];

	Point ims_t;

	bool ispause,isclear;

	int effect_star[5];

	b2Body* jb;

	double line_sc;


};


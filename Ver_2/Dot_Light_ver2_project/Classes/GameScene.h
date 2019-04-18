#pragma once

#include "cocos2d.h"
#include"Box2D/Box2D.h"
#include "GB2ShapeCache-x.h"
#include "enemy.h"
#include "mymath.h"
#include "myray.h"
#include "CCGL.h"
#include <List>
#include "SimpleAudioEngine.h"
#include "extensions\cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
class GameScene : public cocos2d::Layer, public b2ContactListener, public b2RayCastCallback
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

	void add_moveline(Point pt_vert[],int cnt_vert, double speed,Size size, Point anchor_p,double angle);
	void add_movecircle(Point center, double len, Point range_angle, double speed, double h_angle,Size size, Point anchor_p);

	virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	void valueChanged(Ref *sender, Control::EventType controlEvent);

	void set_gl_state(GLProgramState* st,bool on);
	
    // implement the "static create()" method manually
	 virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event);

	 virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	b2Body* addc(Point pos,char sp_anme[], double rad);
	b2Body* addbox(Point pos, Size size, Point anchor_p,char name[]);

	void add_trap(int i, Point pos, Point end_pos, Size size, double angle);

	//여기매우헷갈림
	Point move_box_pt[30][30];//여기에 각 설정들하고 직선으로 움직일 경우는 각각 포인트들이 저장되있음
	int move_cnt;//움직이는 물체가 몇개인지
	int move_cnt_boxs[100];//만약 직선으로 움직일 경우 현재 몇번째 이 물체가 몇번째 구간으로 가고있는지
	double move_speed[100];//당연히 속도
	double move_h_angle[100];//현재 각도(한점을 중심으로 움직이는것)

	double rotation_speed[100];//돌아가는속도(물체자체가 돌아감)
	Point rotation_range[100];//범위

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
	void draw_light(Point pos,double len, float dt);
	void insert_pts(double ray_h_angle, Point value_pts);
	void swap_pts(int wa, int wb);
	Point do_raycast(b2Vec2 start_pos, Point pos, double ray_h_angle, Point vert_ccp, double len, bool issave);
	void drawlines(Point pos);
	void debug_draw();
	void all_map_find_ins(b2Body* h_body, b2Vec2 start_pos, Point pos, Point p1, Point p2, double len);

	void star_effect();
	~GameScene();


	void shader_test();
	GLProgramState* start_shader(Sprite *sp);

	virtual void draw(Renderer* renderer, const kmMat4& transform, uint32_t transformUpdated);
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	void menuCloseCallback(Object *pSender);


	Point trace_line_pt;
	int trace_s,trace_e;
	
	void domenus(Object *obj);

    CREATE_FUNC(GameScene);
private:
	bool map_onoff;

	Size winSize,visibleSize,origin;
	bool isfind;//,isbg;
	int isjoystick, iscontrol;
	double r_angle,before_rangle,before_angle;
	//LabelTTF *label;

	b2World *world;
	b2Body* player;
	Sprite *player_light;
	Point joystick_g,joystick_h, ims_rend2,normalp;
	Sprite *joystick,*joystick_bg;
	Sprite *control_angle, *st_angle;
	double start_angle,bh_angle;
	int raycast_index;
	int ref;
	list<enemy*> enemy_list;
	Sprite *line1, *line2;
	Mymath *mymath;
	Myray *rend1,*rend2;
	Myray *end_ray1[10100];
	ClippingNode *clip_light;
	DrawNode *shape_light;
	Sprite* star_sp[5], *star_gray_sp[5];

	int trap_cnt[20];
	Point trap_btn_pos[20][10];
	Point trap_start_pos[20][10];
	Sprite *trap_sp[10];

	Point start_pos[15],end_pos[15],enemy_pos[15][10],mirror_pos[15],star_pos[15][5];
	int enemy_cnt[15],enemy_speed[15][10];
	bool get_mirror,get_stars[5];

	GLProgramState *st_mirror, *st_star[5];

	Point ims_t;

	bool ispause,isclear;

	int effect_star[5];

	b2Body* jb;

	double line_sc;

	bool iscontact_ray;
	int ray_i;
	Point pts[10100],raycast_pt;
	double rays_angle[10100];
	int ray_num;
	double ray_angle , plus_angle;
	Point h_touch;
};


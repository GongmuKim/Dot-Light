#pragma once
#include"cocos2d.h"
USING_NS_CC;
#include "Box2D\Box2D.h"
#include "mymath.h"
#include "enemy.h"
#include <List>
using namespace std;
class Myray: public b2ContactListener, public b2RayCastCallback
{
private:
	bool iscontact_j,iscontact;
	b2Body *contact_body;
	b2Vec2 start,result;
	Point result_p;

	int result_cnt;
	Mymath *mymath;
	double ref_angle,angle,len;
	b2Body *jb;
	list<enemy*> enemy_list;
	bool is_ref;
public:
	Myray(b2Body *jb, list<enemy*> enemy_list);
	void go_raycast_angle(b2Vec2 pos1,double angle, b2World *world,double len,bool is_ref);
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	b2Vec2 get_result(){return result;}
	Point get_resultp();
	b2Body* get_contact_body() { return contact_body; }
	Point get_startp();
	double get_ref_angle(){return ref_angle;}
	double get_angle(){return angle;}
	bool contact_j(){return iscontact_j;}
	int get_result_cnt() { return result_cnt; }

	Point result_ps[100];
};
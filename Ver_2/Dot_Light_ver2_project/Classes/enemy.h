#pragma once
#include"cocos2d.h"
USING_NS_CC;
#include "Box2D\Box2D.h"
#include "SimpleAudioEngine.h"
class enemy: public b2ContactListener, public b2RayCastCallback
{
private:
	double x,y,speed,range;
	double getdist(double x1,double y1, double x2, double y2);
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	b2Body* body;
	bool isfind,bisfind;
	int sound_loc;
	char name[200];
public:
	enemy(int index,double speed,b2Body* body);
	b2Body* get_body(){return body;}
	void update(float dt,b2World *world,Point ppos,double range);
	void stop(){
		body->SetLinearVelocity(b2Vec2(0,0));
		speed = 0;
	}
	void set_isfind(bool isf) { isfind = isf; }
	void die();
	void stop_sound();
};
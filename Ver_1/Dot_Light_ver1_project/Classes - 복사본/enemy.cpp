#include "enemy.h"
extern CocosDenshion::SimpleAudioEngine *sound;
enemy::enemy(int index,double speed, b2Body* body)
{
	sprintf(name,"sound/enemy%d.mp3",index);
	this->body=body;
	x=body->GetPosition().x*32.0, y=body->GetPosition().y*32.0, this->speed=speed;
	range=300;//반지름
	isfind=false,bisfind=false;
}
void enemy::update(float dt,b2World* world,Point ppos)
{
	x=body->GetPosition().x*32.0, y=body->GetPosition().y*32.0;
	if(this->getdist(ppos.x,ppos.y,body->GetPosition().x*32.0,body->GetPosition().y*32.0)<range){
		world->RayCast(this,body->GetPosition(),b2Vec2(ppos.x/32.0,ppos.y/32.0));
	}
	else isfind=false;

	if(isfind){
		double x=(ppos.x/32.0-body->GetPosition().x)*32.0;
		double y=(ppos.y/32.0-body->GetPosition().y)*32.0;
		double len=sqrt(x*x + y*y);
		body->SetLinearVelocity(b2Vec2(x*speed/len,y*speed/len));
		if(bisfind==false){
			sound_loc=sound->playEffect(name,1);
		}
	}
	else{
		body->SetLinearVelocity(b2Vec2(0,0));
		if(bisfind==true) sound->stopEffect(sound_loc);
	}
	bisfind=isfind;
}
double enemy::getdist(double x1,double y1, double x2, double y2)
{
	double x=x1-x2,y=y1-y2;
	return sqrt(x*x + y*y);
}
float32 enemy::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	if(((Sprite*)fixture->GetBody()->GetUserData())->getTag()==777){
		isfind=true;
	}
	else isfind=false;
	return fraction;
}
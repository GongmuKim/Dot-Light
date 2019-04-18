#include "enemy.h"
extern CocosDenshion::SimpleAudioEngine *sound;
enemy::enemy(int index,double speed, b2Body* body)
{
	//sprintf(name,"sound/trap_on.mp3");
	sprintf(name, "sound/enemy%d.mp3", index);
	//sprintf(name,"sound/ims.mp3");
	this->body=body;
	((Sprite*)this->body->GetUserData())->setName("ENEMY");
	((Sprite*)this->body->GetUserData())->setTag(0);//0:정상 1:따라붙음
	x=body->GetPosition().x*32.0, y=body->GetPosition().y*32.0, this->speed=speed;
	CCLOG("speed:%.1lf\n", speed);
	range=300;//반지름
	isfind=false,bisfind=false;
}
void enemy::update(float dt,b2World* world,Point ppos,double range)
{
	//ppos:플레이어 위치

	/*
	x=body->GetPosition().x*32.0, y=body->GetPosition().y*32.0;
	if(this->getdist(ppos.x,ppos.y,body->GetPosition().x*32.0,body->GetPosition().y*32.0)<range){
		world->RayCast(this,body->GetPosition(),b2Vec2(ppos.x/32.0,ppos.y/32.0));
	}
	else isfind=false;
	*/
	isfind = ((Sprite*)this->body->GetUserData())->getTag();
	if(isfind==1){
		/**/
		double x=(ppos.x/32.0-body->GetPosition().x)*32.0;
		double y=(ppos.y/32.0-body->GetPosition().y)*32.0;
		double len=sqrt(x*x + y*y);
		body->SetLinearVelocity(b2Vec2(x*speed/len,y*speed/len));
	//	body->SetLinearVelocity(b2Vec2(3,3));
		//Point body_ccp = ccp(body->GetPosition().x*32.0,body->GetPosition().y*32.0);
		//body->SetTransform(b2Vec2((body_ccp.x+3)/32.0,(body_ccp.y+3)/32.0), body->GetAngle());
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

void enemy::die()
{
	((Sprite*)body->GetUserData())->setVisible(false);
	body->SetActive(false);
	body->SetTransform(b2Vec2(50 / 32.0, 50 / 32.0), 0);
	((Sprite*)body->GetUserData())->setName("NULL");
	sound->stopEffect(sound_loc);
}

void enemy::stop_sound()
{
	sound->stopEffect(sound_loc);
}
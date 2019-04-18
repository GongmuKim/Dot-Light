#include "myray.h"
Myray::Myray(b2Body *jb, list<enemy*> enemy_list)
{
	mymath=new Mymath();
	result.x=-1000,result.y=-1000;
	start.x=-1000,start.y=-1000;
	iscontact_j=false;
	this->jb=jb;
	this->enemy_list=enemy_list;
}



void Myray::go_raycast_angle(b2Vec2 pos1,double angle, b2World* world,double len,bool is_ref)
{
	this->is_ref = is_ref;
	this->len=len;
	start=pos1;
	this->angle=angle;
	Point pos2= mymath->getline_end(pos1.x*32.0,pos1.y*32.0,angle,len);
	//result.x=pos2.x/32.0,result.y=pos2.y/32.0;
	result_p = pos2;
	iscontact=false;
	
	result_cnt = 0;
	world->RayCast(this,pos1,b2Vec2(pos2.x/32.0,pos2.y/32.0));
}
float32 Myray::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	result = point;
	result_p.x = point.x*32.0, result_p.y = point.y*32.0;
	result_ps[result_cnt++] = result_p;
	iscontact = true;
	//Point dest=ccp(point.x*32.0,point.y*32.0);
	if (is_ref) {
		Point p;
		p.x = point.x, p.y = point.y;
		b2Vec2 v = point - start;
		b2Vec2 n = normal;
		float32 dot = b2Dot(n, v);
		b2Vec2 r2 = 2 * dot*n;
		b2Vec2 r3 = v - r2;
		Point reflectP = ccp((point.x + r3.x), (point.y + r3.y));//*32.0

		ref_angle = mymath->getangle(p, reflectP);
	}
	//contact_body = fixture->GetBody();
	//iscontact_j=false;

	/*
	if (contact_body == jb) iscontact_j = true;
	for (list<enemy*>::iterator it = enemy_list.begin(); it != enemy_list.end(); it++) {
		if (fixture->GetBody() == (*it)->get_body()) iscontact_j = true;
	}*/

	return fraction;
}
Point Myray::get_resultp()
{
	return result_p;
}
Point Myray::get_startp()
{
	Point p;
	p.x=start.x*32.0,p.y=start.y*32.0;
	return p;
}



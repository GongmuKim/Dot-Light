#include "data.h"
int Datas::get_stage_star(int stage,int star)
{
	char name[200]={0};
	sprintf(name,"stage%dstar%d",stage,star);
	return UserDefault::sharedUserDefault()->getIntegerForKey(name);
}
void Datas::set_stage_star(int stage,int star)
{
	char name[200]={0};
	sprintf(name,"stage%dstar%d",stage,star);
	UserDefault::sharedUserDefault()->setIntegerForKey(name,1);
}
int Datas::get_max_stage()
{
	return UserDefault::sharedUserDefault()->getIntegerForKey("openstage");
}
void Datas::set_max_stage(int stage)
{
	UserDefault::sharedUserDefault()->setIntegerForKey("openstage",stage);
}
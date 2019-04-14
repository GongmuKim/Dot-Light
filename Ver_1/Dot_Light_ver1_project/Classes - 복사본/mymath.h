#pragma once
#include"cocos2d.h"
USING_NS_CC;
class Mymath
{
private:
public:
	Mymath(){}
	double getangle(double xg,double yg, double x, double y);
	double getangle(Point p1, Point p2);
	double getdist(double x1,double y1, double x2, double y2);
	double getdist(Point p1, Point p2);
	double angleto0360(double angle);
	Point getline_end(double sx,double sy, double angle, double len);
};
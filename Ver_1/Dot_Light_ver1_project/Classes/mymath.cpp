#include "mymath.h"
double Mymath::getangle(double xg,double yg, double x, double y)
{
	double nx=x-xg, ny=y-yg;
	double nz=sqrt(nx*nx+ny*ny);
	double angle=CC_RADIANS_TO_DEGREES( asin(ny/nz) );
	if(nx>0&&ny>0) angle=angle;
	else if((nx<0&&ny>0)||(nx<0&&ny<0)) angle=180-angle;
	else angle+=360;
	return angle;
}
double Mymath::getdist(double x1,double y1, double x2, double y2)
{
	double x=x1-x2,y=y1-y2;
	return sqrt(x*x + y*y);
}

double Mymath::getangle(Point pg, Point p)
{
	double nx=p.x-pg.x, ny=p.y-pg.y;
	double nz=sqrt(nx*nx+ny*ny);
	double angle=CC_RADIANS_TO_DEGREES( asin(ny/nz) );
	if(nx>0&&ny>0) angle=angle;
	else if((nx<0&&ny>0)||(nx<0&&ny<0)) angle=180-angle;
	else angle+=360;
	return angle;
}
double Mymath::getdist(Point p1, Point p2)
{
	double x=p1.x-p2.x,y=p1.y-p2.y;
	return sqrt(x*x + y*y);
}

Point Mymath::getline_end(double sx,double sy, double angle, double len)
{
	Point result;
	result.x=sx + cos(CC_DEGREES_TO_RADIANS(angle))*len;
	result.y=sy + sin(CC_DEGREES_TO_RADIANS(angle))*len;
	return result;
}
double Mymath::angleto0360(double angle)
{
	double angled=angle-(int)angle;//-15.5
	int angleint=(int)angle%360;
	if(angleint<0){
		int k=(angleint*-1)/360  +1;
		angleint+=k*360;
	}
	return (double)angleint+angled;
}
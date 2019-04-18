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
	return this->angleto0360(angle);
}
double Mymath::getdist(Point p1, Point p2)
{
	double x=p1.x-p2.x,y=p1.y-p2.y;
	return sqrt(x*x + y*y);
}

Point Mymath::getline_end(double sx,double sy, double angle, double len)
{
	angle = angleto0360(angle);
	return ccp(sx + cos(CC_DEGREES_TO_RADIANS(angle))*len, sy + sin(CC_DEGREES_TO_RADIANS(angle))*len);
}

double Mymath::get_dist_ld(Point p1, Point p2, Point dot)
{
	double g=(p2.y-p1.y)/(p2.x-p1.x);//기울기
	double k = p1.y - g*p1.x;
	double d = (g*dot.x + (-dot.y) + k) / sqrt(g*g+1);
	if (d < 0)d *= -1;
	return d;
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
Point Mymath::Intersection_of_point(Point p1, Point p2,    Point p3, Point p4)
{
	Point result_p;
	if (p1.x == p2.x) p1.x += 0.01;
	if (p1.y == p2.y) p1.y += 0.01;
	if (p3.x == p4.x) p3.x += 0.01;
	if (p3.y == p4.y) p3.y += 0.01;

	result_p.x=(p1.x*p2.y - p1.y*p2.x)*(p3.x - p4.x) - (p1.x - p2.x)*(p3.x*p4.y - p3.y*p4.x);
	result_p.x /= (p1.x - p2.x)*(p3.y - p4.y) - (p1.y - p2.y)*(p3.x - p4.x);


	result_p.y = (p1.x*p2.y - p1.y*p2.x)*(p3.y - p4.y) - (p1.y - p2.y)*(p3.x*p4.y - p3.y*p4.x);
	result_p.y /= (p1.x - p2.x)*(p3.y - p4.y) - (p1.y - p2.y)*(p3.x - p4.x);

	Rect p12_rect = Rect(MIN(p1.x, p2.x), MIN(p1.y, p2.y),
		MAX(p1.x - p2.x, p2.x - p1.x), MAX(p1.y - p2.y, p2.y - p1.y));
	Rect p34_rect = Rect(MIN(p3.x, p4.x), MIN(p3.y, p4.y),
		MAX(p3.x - p4.x, p4.x - p3.x), MAX(p3.y - p4.y, p4.y - p3.y));
	if (p12_rect.containsPoint(result_p) == false || p34_rect.containsPoint(result_p) == false) return ccp(-1, -1);
	return result_p;
}

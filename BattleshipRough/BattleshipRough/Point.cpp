#include"Point.h"

#include <iostream>

using namespace std;

Point::Point()
{
	x = 0;
	y = 0;
}
Point:: Point(int inst_x, int inst_y)
{
	x = inst_x;
	y = inst_y;
}

ostream& operator<<(ostream& os, const Point& point)
{
	char xChar = 'A' + point.x;
	os << xChar << point.y; // should print this struct as "12" := row 1, column 2
	return os;
}
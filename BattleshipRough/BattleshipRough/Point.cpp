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
	char xChar = 'A' + point.x; // Convert column integer 0-9 to letters A-I
	// Y Point values range from 0-9, should print as 1-10
	os << xChar << point.y + 1;
	return os;
}
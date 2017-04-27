#ifndef POINT_H
#define POINT_H
#include <ostream>

using namespace std;

struct Point
{
	//char x;
	// x row is characters A-J

	int x;
	int y;
	Point();
	Point(int inst_x, int inst_y);
	bool operator==(const Point& rhs) const;
	friend ostream& operator<<(ostream& os, const Point& point);
	
};
#endif //POINT_H
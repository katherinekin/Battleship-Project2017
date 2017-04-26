#ifndef ENEMY_H
#define ENEMY_H
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
	friend Point operator==(const Point& lhs, const Point& rhs);
	friend ostream& operator<<(ostream& os, const Point& point);
	
};
#endif //ENEMY_H
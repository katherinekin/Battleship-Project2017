#pragma once
#include <ostream>

using namespace std;

struct Point
{
	//char x;
	// x row is characters A-J

	int x;
	int y;
	char xChar;
	Point();
	Point(int inst_x, int inst_y);
//<<<<<<< HEAD

	void userAssigned();
	int xStringToIndex(char& c);
	int yInputToIndex();
	bool isEqualTo(Point p);
	//friend Point operator==(const Point& lhs, const Point& rhs);
//=======
	bool operator==(const Point& rhs) const;
//>>>>>>> Katherine2
	friend ostream& operator<<(ostream& os, const Point& point);

};
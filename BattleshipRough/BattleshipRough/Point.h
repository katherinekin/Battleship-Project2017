#ifndef POINT_H
#define POINT_H
#include <iostream>

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
	Point(char inst_x, int inst_y);

	void userInput();
	int xStringToIndex(char& c);
	int yInputToIndex();
	friend Point operator==(const Point& lhs, const Point& rhs);
	friend ostream& operator<<(ostream& os, const Point& point);

};
#endif //POINT_H
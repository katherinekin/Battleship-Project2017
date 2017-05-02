#include"Point.h"
#include <string>
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

void Point::userAssigned()
{
	int yI, xI;
	char xC;
	bool run = true;
	while (run)
	{
		cout << "Enter Starting Point" << endl;
		xI = xStringToIndex(xC);
		yI = yInputToIndex();
		cout << "Did you mean " << xC << yI + 1 << "? Y/N: ";
		string input;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
		if (input[0] == 'Y' || input[0] == 'y')
		{
			run = false;
		}
	}
	
	this->xChar = xC;
	this->x = xI;
	this->y = yI;
}

int Point::xStringToIndex(char& c)
{
	int xI;
	string xS;
	char xC;
	bool run = true;
	while (run)
	{
		cout << "Enter Column {A-J or a-j}: ";
		cin >> xS;
		xC = xS[0];
		xI = int(xC);
		if (xI >= 97 && xI <= 106) {
			xI -= 97;
			run = false;
		}
		else if (xI >= 65 && xI <= 74) {
			xI -= 65;
			run = false;
		} else {
			cout << "Input Error, please try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			xI = 0;
			xS = "";
		}
	}
	c = xC;
	return xI;
}

int Point::yInputToIndex()
{
	int yI;
	bool run = true;
	while (run)
	{
		cout << "Enter Row {1-10}: ";
		cin >> yI;
		if (yI <= 10 && yI >= 1) {
			yI--;						// Board is 1-10; Array is 0-9; so, subtract one.
			run = false;
		}
		else {
			cout << "Input Error, please try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	return yI;
}

ostream& operator<<(ostream& os, const Point& point)
{
	char xChar = 'A' + point.x; // Convert column integer 0-9 to letters A-I
	// Y Point values range from 0-9, should print as 1-10
	os << xChar << point.y + 1;
	return os;
}
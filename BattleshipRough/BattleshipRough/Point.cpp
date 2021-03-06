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
	char yS;
	char xC;
	bool run = true;
	int errors;
	string ui = "";
	while (run)
	{
		cout << "Enter a point (e.g. A6 or J10, etc.): ";
		cin >> ui;
		xC = ui[0];
		xI = int(ui[0]);

		if (xI >= 97 && xI <= 106) {
			xI -= 97;
		}
		else if (xI >= 65 && xI <= 74) {
			xI -= 65;
		}
		else {
			cout << "Column Input Error, please try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			xI = 0;
			ui = "";
		}
		yS = ui[1]; // ASCII code for '0' is 48
		if (yS == '1')
		{
			if (ui[2] == '0')
				yI = 10;
			else
				yI = 1;
		}
		else if(int(yS) > 47 && int(yS) < 58)
		{
			yI = int(ui[1]) - 48;
		}
		else
		{
			cout << "Row Input Error, please try again." << endl;
			yI = 1;
		}
		cin.clear();
		cin.ignore(10000, '\n');
		if (yI <= 10 && yI >= 1) 
		{
			yI--;						// Board is 1-10; Array is 0-9; so, subtract one.
		}
		else 
		{
			cout << "Row Input Error, please try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}

		cout << "Did you mean " << xC << yI + 1 << "? Y/N: ";
		string input;
		cin.clear();
		//cin.ignore(10000, '\n');
		cin >> input;
		if (input[0] == 'Y' || input[0] == 'y')
		{
			run = false;
		}
		else if (input[0] == 'N' || input[0] == 'n')
		{
			// intentionally empty
			cout << "Try again." << endl;
			cin.clear();
			cin.ignore();
			input = "";
			ui = "";
		}
		else
		{
			cout << "There was some kind of error; Try this way:" << endl;
			xI = xStringToIndex(xC);
			yI = yInputToIndex();
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

bool Point::isEqualTo(Point p)
{
	bool isEqual;
	if (this->x == p.x && this->y == p.y)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& os, const Point& point)
{
	char xChar = 'A' + point.x; // Convert column integer 0-9 to letters A-I
	// Y Point values range from 0-9, should print as 1-10
	os << xChar << point.y + 1;
	return os;
}
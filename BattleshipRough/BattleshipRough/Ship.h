#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Point.h"
using namespace std;

class Ship
{
public:
	Ship();
	Ship(int noOfSpaces, string shipName, char shipChar);

	int getNoOfSpaces();
	void setNoOfSpaces(int noOfSpaces);

	string getShipName();
	void setShipName(string shipName);

	char getShipChar();
	void setShipChar(char shipChar);

	bool getVertical();
	void setVertical(bool vertical);

private:
	int _noOfSpaces;
	string _shipName;
	char _shipChar;
	bool _vertical, _sunk;
	Point _startingPoint;
	vector<Point> _points;
};
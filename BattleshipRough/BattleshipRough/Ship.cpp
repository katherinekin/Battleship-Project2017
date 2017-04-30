#include "Ship.h"
#include <iostream>
using namespace std;
Ship::Ship(int noOfSpaces, string shipName, char shipChar)
{
	_noOfSpaces = noOfSpaces;
	_shipName = shipName;
	_shipChar = shipChar;
	bool run = true;
	while (run)
	{
		cout << "Select a starting location for your " << shipName << endl;
		cout << "It takes up " << noOfSpaces << " spaces." << endl;
		_startingPoint.userAssigned();
		cout << _startingPoint << endl;
		string input;
		bool run2 = true;
		while (run2)
		{
			cout << "Horizontal or Vertical?" << endl << "Type H or V and press enter." << endl;
			cin >> input;
			if (input[0] == 'h' || input[0] == 'H')
			{
				_vertical = false;
				run2 = false;
			}
			else if (input[0] == 'v' || input[0] == 'V')
			{
				_vertical = true;
				run2 = false;
			}
			else
			{
				cout << "Try Again." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		int endingPoint;
		if (!_vertical)
			endingPoint = _startingPoint.x + _noOfSpaces;
		else if (_vertical)
			endingPoint = _startingPoint.y + _noOfSpaces;
		else
		{
			cout << "The vertical method variable was not set. Try again." << endl;
		}

		if (endingPoint < 10 && endingPoint >= 0)
			run = false;
		else
			cout << "The ship goes out of bounds! Try again." << endl;
	}
	Point temp(_startingPoint.x, _startingPoint.y);
	_points.push_back(temp);
	if (!_vertical)
	{
		for (int i = 1; i < _noOfSpaces; i++)
		{
			temp.x += 1;
			_points.push_back(temp);
		}
	}
	else if (_vertical)
	{
		for (int i = 1; i < _noOfSpaces; i++)
		{
			temp.y += 1;
			_points.push_back(temp);
		}
	}
	cout << "Your " << shipName << " will occupy the following points: ";
	for (int i = 0; i < _points.size(); i++)
	{
		cout << _points[i] << " ";
	}
	cout << endl;
	system("pause");
	system("cls");
}

int Ship::getNoOfSpaces()
{
	return _noOfSpaces;
}

void Ship::setNoOfSpaces(int noOfSpaces)
{
	_noOfSpaces = noOfSpaces;
}

string Ship::getShipName()
{
	return _shipName;
}

void Ship::setShipName(string shipName)
{
	_shipName = shipName;
}

char Ship::getShipChar()
{
	return _shipChar;
}

void Ship::setShipChar(char shipChar)
{
	_shipChar = shipChar;
}

bool Ship::getVertical()
{
	return _vertical;
}

void Ship::setVertical(bool vertical)
{
	_vertical = vertical;
}

vector<Point> Ship::getPoints()
{
	return _points;
}

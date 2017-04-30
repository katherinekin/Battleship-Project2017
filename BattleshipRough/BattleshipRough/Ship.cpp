#include "Ship.h"
#include <iostream>
using namespace std;
Ship::Ship(int noOfSpaces, string shipName, char shipChar)
{
	_noOfSpaces = noOfSpaces;
	_shipName = shipName;
	_shipChar = shipChar;
	_startingPoint.userInput();
	cout << _startingPoint << endl;
	cout << "Horizontal or Vertical? Type H or V and press enter." << endl;
	string input;
	bool run = true;
	while (run)
	{
		cin >> input;
		if (input[0] == 'h' || 'H')
		{
			_vertical = false;
			run = false;
		}
		else if (input[0] == 'v' || 'V')
		{
			_vertical = true;
			run = false;
		}
		else
			cout << "Try Again." << endl;
	}
	for (int i = 0; i < _noOfSpaces; i++)
	{

	}
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

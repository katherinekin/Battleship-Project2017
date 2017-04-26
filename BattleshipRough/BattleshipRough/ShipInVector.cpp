#include"ShipInVector.h"

ShipInVector::ShipInVector()
{
	_someVect;
	_p = Point(0, 0);
}
ShipInVector::~ShipInVector()
{
	//
}
ShipInVector::ShipInVector(vector<Point> v, Point p)
{
	_someVect = v;
	_p = p;
}
void ShipInVector::findShipInVector()
{
	/*
	int x = _p.x;
	int y = _p.y;

	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	for (int i = _.size() - 1; i >= 0; i--)
	{
		Point p = _locs.at(i);
		if (p.x == a && p.y == y)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
		if (p.x == b && p.y == y)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
		if (p.x == x && p.y == c)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
		if (p.x == x && p.y == d)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
	}
	*/
}
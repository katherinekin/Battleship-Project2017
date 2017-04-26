#ifndef SHIPINVECTOR_H
#define SHIPINVECTOR_H
#include"Point.h"
#include<vector>

using namespace std;

class ShipInVector
{
public:
	ShipInVector();
	~ShipInVector();
	ShipInVector(vector<Point> v, Point p);
	void findShipInVector();
private:
	vector<Point> _someVect;
	Point _p;
};
#endif //SHIPINVECTOR_H

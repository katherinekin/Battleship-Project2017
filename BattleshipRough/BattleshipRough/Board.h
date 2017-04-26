#pragma once

#include <iostream>
#include <vector>
#include "Point.h"

using namespace std;

class Board
{
public:

	Board();
	~Board();

	void setPointState(Point p, bool state);
	bool getPointState(Point p);

	vector<Point> getLocs();
	void setLocs(vector<Point> locs);
	
	vector<Point> getCheckLater();
	void setCheckLater(vector<Point> checkLater);
	
	int* getBoardArray();
	void setBoardArray(int* boardArray);

	int** getTemp();
	void setTemp(int** temp);

	friend ostream& operator<<(ostream& os, const Board board);

private:
	int* _boardArray;
	int** _temp;
	vector<Point> _locs = vector<Point>(100);
	vector<Point> _checkLater;
};
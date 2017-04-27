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

	void setLocs(vector<Point> locs);
	vector<Point> getLocs();

	void setCheckLater(vector<Point> checkLater);
	vector<Point> getCheckLater();
	
	void setBoardArray(int* boardArray);
	int* getBoardArray();

	void setTemp(int** temp);
	int** getTemp();

	void setState(bool state);	// A state of 1 indicates the computer should be
	bool getState();			// making targeted attacks following a 'hit'

	friend ostream& operator<<(ostream& os, const Board board);

private:
	int* _boardArray;			// Array of points for the board as a 1-D array
	int** _temp;				// 2-D array - 10 pointers for each row
	vector<Point> _locs = vector<Point>(100);	// Points still to target.
	vector<Point> _checkLater;	// Points to check later
	bool _state;				// Returns whether or not the computer is making targeted attacks
};
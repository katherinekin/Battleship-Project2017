#pragma once

#include <iostream>
#include <vector>
#include "Ship.h"
#include "Point.h"

using namespace std;

class Board
{
public:

	Board();
	~Board();
	void setCpuPlayer(bool cpuPlayer);
	bool getCpuPlayer();
	int sunkenShips;
	/*
	virtual void turn() { 
		// empty 
	}
	*/
	void setPointState(Point p, int state);
	int getPointState(Point p);

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

	bool addShip(const Ship s);
	vector<Ship> getShips();

	friend ostream& operator<<(ostream& os, const Board board);

private:
	int* _boardArray;							// Array of points for the board as a 1-D array
	int** _temp;								// 2-D array - 10 pointers for each row
	vector<Point> _locs = vector<Point>(100);	// Points still to target.
	vector<Point> _checkLater;					// Points to check later
	bool _state, _cpuPlayer;								// Returns whether or not the computer is making targeted attacks
	vector<Ship> _ships;
};
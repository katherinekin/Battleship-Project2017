#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "Point.h"
#include "Ship.h"
#include "PlaceShip.h"
#include "Player.h"
#include "Board.h"

using namespace std;

class Enemy : public Board
{
public:
	Enemy();
	~Enemy();
	Enemy(vector<Point> &locs, vector<Point> &checkLater, bool state, vector<Ship> &someShips);

	void turn(Board &board);
	void RandomHitOrMiss(int **temp, Board &board);
	void FocusedHitOrMiss(int **temp, int index, Point p, Board &board);

	//vector<Point> getHits();
	//vector<Ship> getShips();

	void Hit(int index, Point p, Board &board);
	void Miss(int index, Point p);

	void removeAdjSpaces(int x, int y);
	void firstStrike(Board &board);
	void FindTheShip(int **temp, Board &board);

	void Print();

	Point getLastStrike();
	
		
private:
	//vector<Point> _locs;
	//vector<Point> _checkLater;
	//vector<Point> _hits;
	//vector<Point> _misses;
	//vector<Ship> _someShips;
	vector<Ship> _hitShips;

	Point _lastStrike;
	bool _state;

	////////
	//vector<Point> 
	vector<Point> _carrier;
	vector<Point> _battleship;
	vector<Point> _cruiser;
	vector<Point> _submarine;
	vector<Point> _destroyer;
	//vector< vector<Point> >
	vector< vector<Point> >_hits = { _carrier, _battleship, _cruiser, _submarine, _destroyer };
	Point _lastHit;
	int _ShipVectIndex;
	int findMax(vector<Point> &currentShip, bool vertical);
	int findMin(vector<Point> &currentShip, bool vertical);
};

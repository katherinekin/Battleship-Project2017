#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Enemy.h"

using namespace std;

class Player : public Board
{
public:
	Player();
	~Player();
	Player(vector<Point> &locs, vector<Ship> &someShips);

	int sunkenShips;

	void turn(int **temp, int board[], Board enemyBoard);
	void turn(Board board);


	void Hit(Point p);
	void Miss(Point p);

	vector<Point> getHits();
	//vector<Ship> getShips();

	Point getLastStrike();


private:
	//vector<Point> _locs;
	vector<Point> _hits;
	vector<Point> _misses;
	//vector<Ship> _someShips;
	vector<Ship> _hitShips;

	Point _lastStrike;
	bool _state;
};

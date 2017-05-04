#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Point.h"
#include"Ship.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();
	Player(vector<Point> &locs, vector<Ship> &someShips);

	void turn(int **temp, int board[]);

	void hitOrMiss(int **temp, int board[]);
	void Hit(Point p);
	void Miss(Point p);

	vector<Point> getHits();
	vector<Ship> getShips();



	Point getLastStrike();


private:
	vector<Point> _locs;
	vector<Point> _hits;
	vector<Point> _misses;
	vector<Ship> _someShips;
	vector<Ship> _hitShips;

	Point _lastStrike;
	bool _state;
};
#endif //ENEMY_H

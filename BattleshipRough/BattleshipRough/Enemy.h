#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Point.h"
#include"Ship.h"

using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
	Enemy(vector<Point> &locs, vector<Point> &checkLater, bool state, vector<Ship> &someShips);

	void turn(int **temp, int board[]);
	void RandomHitOrMiss(int **temp, int board[]);
	void FocusedHitOrMiss(int **temp, int board[], int index, Point p);

	void Hit(int index, Point p);
	void Miss(int index, Point p);

	//void removeAdjSpaces(int x, int y);
	void RemoveHits(Ship ship);
	void firstStrike();
	void FindTheShip(int **temp, int board[]);

	int findMax(vector<Point> &currentShip, bool vertical);
	int findMin(vector<Point> &currentShip, bool vertical);

	bool WinCondition();
	void Print();

	Point getLastStrike();
	
		
private:
	vector<Point> _locs;
	vector<Point> _checkLater;

	vector< vector<Point> > _hits;
	vector<Point> _carrier;
	vector<Point> _battleship;
	vector<Point> _cruiser;
	vector<Point> _submarine;
	vector<Point> _destroyer;

	vector<Point> _misses;
	vector<Ship> _someShips;
	vector<Ship> _hitShips;

	int _ShipVectIndex;
	Point _lastHit;

	Point _lastStrike;
	bool _state;
	bool _win;
};
#endif //ENEMY_H

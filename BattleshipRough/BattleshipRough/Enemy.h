#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Point.h"

using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
	Enemy(vector<Point> &locs, vector<Point> &checkLater, bool state);

	void turn(int **temp, int board[]);
	void HitOrMiss(int **temp, int board[]);
	void Miss(int index, Point p);
	void removeAdjSpaces(int x, int y);
	void findtheShip(int x, int y);
		
private:
	vector<Point> _locs;
	vector<Point> _checkLater;
	bool _state;
};
#endif //ENEMY_H

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
	void RandomHitOrMiss(int **temp, int board[]);
	void FocusedHitOrMiss(int **temp, int board[], int index, Point p);

	void Hit(int index, Point p);
	void Miss(int index, Point p);

	void removeAdjSpaces(int x, int y);
	void FindTheShip(int **temp, int board[]);

	void Print();
	
		
private:
	vector<Point> _locs;
	vector<Point> _checkLater;
	vector<Point> _hits;
	bool _state;
};
#endif //ENEMY_H

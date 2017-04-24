#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Enemy.h"

using namespace std;

Enemy::Enemy()
{
		//rewrite the vector statements
	_locs;
	_checkLater;
	_state = 0;
}
Enemy::~Enemy()
{
	//
}
Enemy::Enemy(vector<Point> &locs, vector<Point> &checkLater, bool state)
{
	_locs = locs;
	_checkLater = checkLater;
	_state = state;
}
	//
void Enemy::turn(int **temp, int board[])
{
	//cout << "Computer's turn: "
	cout << "Hit enter for the computer to take a turn" << endl;
	if (_state == 0)
	{
		HitOrMiss(temp, board);
	}
	if (_state == 1)
	{
			//FindTheShip();
	}

}
void Enemy::HitOrMiss(int **temp, int board[])
{
	int index = rand() % _locs.size();

	Point p = _locs.at(index);
	int x = p.x;
	int y = p.y;
	
	if (temp[x][y] == 1)
	{
		cout << p << endl;
		cout << "HIT" << endl;
			//check if the ship has sunk
			//if not sunk, call function to look for ship
		_state = 1;
	}
	else
	{
		cout << p << endl;
		cout << "MISS" << endl;

		//write this in a new function, that calls adjacent spaces
		Miss(index, p);
		_state = 0;
	}

	int locsize = _locs.size();
	for (int i = 0; i < locsize; i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _locs.at(i) << "   ";
	}

	cout << endl;
	int clsize = _checkLater.size();
	for (int i = 0; i < clsize; i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _checkLater.at(i) << "   ";
	}
	cout << endl;
}


void Enemy::Miss(int index, Point p)
{
	_locs.erase(_locs.begin() + index);

	//call function to also remove adjacent spaces
	removeAdjSpaces(p.x, p.y);
	cout << p.x << ", " << p.y << " is a miss!" << endl;
}

	//remove the missed space and the adjacent spaces, called by hit or miss
void Enemy::removeAdjSpaces(int x, int y)
{

	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	//if a, b, c, d are <0 or >9, will not be removed
	//(a, y) (b, y) (x, c) (y, d)
	//need to place in another vector for potential spaces to check, shouldn't remove
	//counting backwards to avoid missing spaces...works!
	
	int locsize = _locs.size();
	for (int i = locsize - 1; i >= 0; i--)
	{
		Point p = _locs.at(i);
		//check edge cases
		if (p.x == a && p.y == y)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
		if (p.x == b && p.y == y)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
		if (p.x == x && p.y == c)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
		if (p.x == x && p.y == d)
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
	}
}

void Enemy::findtheShip(int x, int y)
{
	//(a, y) (b, y) (x, c) (y, d)
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	//keep going until a ship has been sunk
	//create a new vector findShip that combines locs and checkLater, sort
	//for loop that runs through findShip for combos of 
}

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
	_hits;
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
	_hits;
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
		//FindTheShip(temp, board);
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
		Hit(index, p);
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
void Enemy::Hit(int index, Point p)
{
	_hits.push_back(p);
	//should call the draw function to change graphics of the board corresponding to HIT
	_locs.erase(_locs.begin() + index);
}
void Enemy::Miss(int index, Point p)
{
	_locs.erase(_locs.begin() + index);	//removes the missed space from spaces to check permanently
	//should call the draw function to change graphics of the board corresponding to MISS
	//call function to also remove adjacent spaces
	removeAdjSpaces(p.x, p.y);
}
void Enemy::removeAdjSpaces(int x, int y)
{
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	//if a, b, c, d are <0 or >9, will not be detected in the vector
	//(a, y) (b, y) (x, c) (y, d)
	//need to place in another vector for potential spaces to checkLater
	//counting backwards so that when the point is removed and the indices are changed, does not skip points
	
	for (int i = _locs.size() - 1; i >= 0; i--)
	{
		Point p = _locs.at(i);
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

/* Need to fix
void Enemy::FindTheShip(int **temp, int board[])
{
	//(a, y) (b, y) (x, c) (y, d)
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	int ship = 1;
	//create a new vector that holds all the spots with hits
	//if this vector is empty, _state becomes 0

	if (_hits.size() < 1)
	{
		_state = 0;
	}

	//create a new vector findShip that combines locs and checkLater, don't sort
	vector<Point> findShip = _locs;
	findShip.insert(findShip.end(), _checkLater.begin(), _checkLater.end());

	//keep going until a ship has been sunk, if ship not sunk
	//while number of ships is not less than current number and number of ships is not equal to zero
	

	//for loop that runs through findShip for combos of 
}
*/

/*Move this to a new header file
void Enemy::ShipInVector(vector<Point> v, Point p)
{
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	for (int i = _locs.size() - 1; i >= 0; i--)
	{
		Point p = _locs.at(i);
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
*/

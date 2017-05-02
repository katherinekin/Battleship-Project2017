#include <iostream>
#include<random>
#include<algorithm>
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
	_misses;
	_state = state;
	_lastStrike;
}
	//
void Enemy::turn(int **temp, int board[])
{	
	if (_state == 0)
	{
		RandomHitOrMiss(temp, board);
	}
	else if (_state == 1)
	{
		FindTheShip(temp, board);
	}

}
void Enemy::RandomHitOrMiss(int **temp, int board[])
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

		Miss(index, p);
		_state = 0;
	}
	_lastStrike = p;
}

void Enemy::FocusedHitOrMiss(int **temp, int board[], int index, Point p)
{
	int x = p.x;
	int y = p.y;

	if (temp[x][y] == 1)	//If ship is there
	{
		cout << "FOCUSED HIT" << endl;
		Hit(index, p);
	}
	else
	{
		cout << "FOCUSED MISS" << endl;
		Miss(index, p);
	}
	_lastStrike = p;
}

void Enemy::Hit(int index, Point p)
{
	_hits.push_back(p);
	//should call the draw function to change graphics of the board corresponding to HIT
	//check if p is in _locs or _checkLater before deleting
	int x = p.x;
	int y = p.y;
	for (int i = 0; i < _locs.size(); i++)
	{
		if (x == _locs.at(i).x && y == _locs.at(i).y)
		{
			_locs.erase(_locs.begin() + i);
		}

	}
	for (int i = 0; i < _checkLater.size(); i++)
	{
		if (x == _checkLater.at(i).x && y == _checkLater.at(i).y)
		{
			_checkLater.erase(_checkLater.begin() + i);
		}
	}

	Print();
	cout << endl;
}

void Enemy::Miss(int index, Point p)
{
	//removes the missed space from spaces to check permanently
	//check if p is in _locs or _checkLater before deleting
	int x = p.x;
	int y = p.y;
	
	_misses.push_back(p);
	for (int i = 0; i < _locs.size(); i++)
	{
		if (x == _locs.at(i).x && y == _locs.at(i).y)
		{
			_locs.erase(_locs.begin() + i);
		}
		
	}
	for (int i = 0; i < _checkLater.size(); i++)
	{
		if (x == _checkLater.at(i).x && y == _checkLater.at(i).y)
		{
			_checkLater.erase(_checkLater.begin() + i);
		}
	}
	
	//should call the draw function to change graphics of the board corresponding to MISS
	//call function to also remove adjacent spaces
	removeAdjSpaces(p.x, p.y);

	Print();
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
		if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
		{
			_locs.erase(_locs.begin() + i);
			_checkLater.push_back(p);
			cout << "Removed " << p << endl;
		}
	}
}

void Enemy::FindTheShip(int **temp, int board[])
{
	//create a new vector findShip that combines locs and checkLater, don't sort
	//vector<Point> findShip = _locs;
	//findShip.insert(findShip.end(), _checkLater.begin(), _checkLater.end());	//concatenates _locs and _checkLater, index in for Loop corresponds

	
	//go by number of ships before state change
	//go by number of hit spots (better)
	//finding the first two spots most important
	//edge case: if there are two ships side by side
	
	Point hit = _hits.back();	//returns the last Point in _hits
	int x = hit.x;
	int y = hit.y;
	cout << hit << " was hit, time to test" << endl;

	//(a, y) (b, y) (x, c) (y, d)
	//create a new vector that holds all the spots with hits
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;
	
	for (int index = _locs.size() - 1; index >= 0; index--)
	{
		Point p = _locs.at(index);
		if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
		{
			cout << "I will check if there is a ship in: " << p <<endl;
			FocusedHitOrMiss(temp, board, index, p);
			break;	//computer can only guess one spot per turn!
		}
		
	}
	for (int index = 0; index < _checkLater.size(); index++)
	{
		Point p = _checkLater.at(index);
		if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
		{
			cout << "I will check if there is a ship in: " << p <<endl;
			FocusedHitOrMiss(temp, board, index, p);
			break;	//computer can only guess one spot per turn!
		}
	}

	//if this vector is empty, _state becomes 0
	if (_hits.size() < 1)
	{
		_state = 0;
	}

	//keep going until a ship has been sunk, if ship not sunk
	//while number of ships is not less than current number and number of ships is not equal to zero
}
void Enemy::Print()	//Prints the vectors _locs, _checkLater, and _hits for troubleshooting
{
	//Print out _locs and _checkLater
	cout << "_locs contains "<<endl;
	for (int i = 0; i < _locs.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _locs.at(i) << "   ";
	}
	cout << endl;
	cout << "_checkLater contains "<<endl;
	for (int i = 0; i < _checkLater.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _checkLater.at(i) << "   ";
	}
	cout << endl;
	cout << "_hits contains "<<endl;
	for (int i = 0; i < _hits.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _hits.at(i) << "   ";
	}
	cout << endl;
	cout << "_misses contains " << endl;
	for (int i = 0; i < _misses.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _misses.at(i) << "   ";
	}
	cout << endl;
}

Point Enemy::getLastStrike()
{
	return _lastStrike;
}


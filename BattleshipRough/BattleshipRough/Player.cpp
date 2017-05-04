#include "Player.h"

Player::Player()
{
	//rewrite the vector statements
	_locs;
	_hits;
	_misses;

}

Player::~Player()
{
}

Player::Player(vector<Point>& locs, vector<Ship>& someShips)
{
	_locs = locs;
	_hits;
	_misses;
	_someShips = someShips;	//when this is empty, win condition
	_hitShips;
	_lastStrike;
}

void Player::turn(int ** temp, int board[])
{
	Point p;
	p.userAssigned();
	system("cls");
	if (temp[p.x][p.y] != 1 && temp[p.x][p.y] != 0)
		cout << "You already tried that space. You lose your turn." << endl;
	else
	{
		if (temp[p.x][p.y] == 1)
		{
			cout << "HIT" << endl;
			Hit(p);
		}
		else
		{
			cout << "MISS" << endl;
			Miss(p);
		}

	}
	_lastStrike = p;
}

void Player::hitOrMiss(int ** temp, int board[])
{

}

void Player::Hit(Point p)
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

	cout << endl;
}

void Player::Miss(Point p)
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

}

vector<Point> Player::getHits()
{
	return _hits;
}

vector<Ship> Player::getShips()
{
	return _someShips;
}



Point Player::getLastStrike()
{
	return _lastStrike;
}

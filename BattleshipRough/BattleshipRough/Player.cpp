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


	firstStrike();

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

void Player::firstStrike()
{
	//Loop through to find which ship was hit, sets the size needed to sink the ship
	Point hit = _hits.back();
	bool FoundShip = false;
	Ship ship;

	for (int i = _someShips.size() - 1; i >= 0; i--)
	{
		ship = _someShips.at(i);
		vector<Point> coord = ship.getPoints();

		for (int j = coord.size() - 1; j >= 0; j--)
		{
			Point p = coord.at(j);

			if (p.x == hit.x && p.y == hit.y)
			{
				//get ship name
				cout << "The ship I am looking for is the " << ship.getShipName() << endl;
				cout << "The size of this ship is " << ship.getNoOfSpaces() << endl;
				//get ship size
				//set size to look for ship
				ship.setNoOfSpaces(ship.getNoOfSpaces() - 1);
				_hitShips.push_back(ship);	//adds ship with new size;
				_someShips.erase(_someShips.begin() + i);

				cout << "The size of this ship is now " << ship.getNoOfSpaces() << endl;
				FoundShip = true;

				break;
			}
		}
	}

	if (FoundShip == false)
	{
		for (int i = _hitShips.size() - 1; i >= 0; i--)
		{
			ship = _hitShips.at(i);
			vector<Point> coord = ship.getPoints();

			for (int j = coord.size() - 1; j >= 0; j--)
			{
				Point p = coord.at(j);
				if (p.x == hit.x && p.y == hit.y)
				{
					cout << "The ship I am looking for is in _hitShips, and is the " << ship.getShipName() << endl;
					cout << "The size of this ship was " << ship.getNoOfSpaces() << endl;

					ship.setNoOfSpaces(ship.getNoOfSpaces() - 1);
					_hitShips.erase(_hitShips.begin() + i);
					_hitShips.push_back(ship);

					cout << "The size of this ship is now " << ship.getNoOfSpaces() << endl;
					FoundShip = true;
					if (ship.getNoOfSpaces() == 0)
					{
						cout << "The " << ship.getShipName() << " has been sunk!" << endl;
						_hitShips.erase(_hitShips.begin() + i);
						//remove all coordinates from _hits
						break;
					}
				}
			}
		}
	}

	if (_hitShips.size() == 0)
		_state = 0;
	
}

Point Player::getLastStrike()
{
	return _lastStrike;
}

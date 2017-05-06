#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Enemy.h"


using namespace std;

Enemy::Enemy() : Board()
{
		//rewrite the vector statements
	//_locs;
	_checkLater;
	_hits;
	_misses;
	_state = 0;
	_hitShips;
	_lastStrike;
}
Enemy::~Enemy()
{
	//
}
Enemy::Enemy(vector<Point> &locs, vector<Point> &checkLater, bool state, vector<Ship> &someShips) : Board()
{
	//_locs = locs;
	_checkLater = checkLater;
	_hits;
	_misses;
	_state = state;
	//_someShips = someShips;	//when this is empty, win condition
	_hitShips;
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
void Enemy::turn(Board board)
{
	if (_state == 0)
	{
		RandomHitOrMiss(board.getTemp(), board.getBoardArray());
	}
	else if (_state == 1)
	{
		FindTheShip(board.getTemp(), board.getBoardArray());
	}
	Point ls = getLastStrike();
	vector<Point> points;
	if (board.getPointState(ls) == 1)
	{
		board.setPointState(ls, 9);
		bool isShip = false;
		for (int i = 0; i < board.getShips().size(); i++)
		{
			points = board.getShips()[i].getPoints();
			for (int j = 0; j < points.size(); j++)
			{
				if (ls.x == points[j].x && ls.y == points[j].y)
				{
					isShip = true;
				}
			}
			if (isShip == true)
			{
				board.getShips()[i].setNoOfSpaces(board.getShips()[i].getNoOfSpaces() - 1);
				cout << "They hit your " << board.getShips()[i].getShipName() << " (" << board.getShips()[i].getNoOfSpaces() << " spaces left)" << endl;
				if (board.getShips()[i].getNoOfSpaces() == 0)
				{
					cout << "They've sunk your " << board.getShips()[i].getShipName() << "!" << endl;
					board.sunkenShips++;
				}
			}
			isShip = false;
		}
	}
	else
		board.setPointState(ls, 5);
}
void Enemy::RandomHitOrMiss(int **temp, int board[])
{
	int index = rand() % this->getLocs().size();

	Point p = this->getLocs().at(index);
	int x = p.x;
	int y = p.y;
	
	if (temp[x][y] == 1)
	{
		cout << p << endl;
		cout << "They guessed " << p << " -- HIT" << endl;
			//check if the ship has sunk
			//if not sunk, call function to look for ship
		Hit(index, p);
		_state = 1;
	}

	else
	{
		cout << p << endl;
		cout << "They guessed " << p << " -- MISS" << endl;

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
		cout << "They guessed " << p << " -- FOCUSED HIT" << endl;
		Hit(index, p);
	}
	else
	{
		cout << "They guessed " << p << " -- FOCUSED MISS" << endl;
		Miss(index, p);
		_state = 0;
	}
	_lastStrike = p;
}

vector<Point> Enemy::getHits()
{
	return _hits;
}

/*
vector<Ship> Enemy::getShips()
{
	return _someShips;
}
*/
void Enemy::Hit(int index, Point p)
{
	_hits.push_back(p);
	//should call the draw function to change graphics of the board corresponding to HIT
	//check if p is in _locs or _checkLater before deleting
	int x = p.x;
	int y = p.y;
	vector<Point> locs = this->getLocs();
	for (int i = 0; i < locs.size(); i++)
	{
		if (x == locs.at(i).x && y == locs.at(i).y)
		{
			locs.erase(locs.begin() + i);
		}
	}

	for (int i = 0; i < _checkLater.size(); i++)
	{
		if (x == _checkLater.at(i).x && y == _checkLater.at(i).y)
		{
			_checkLater.erase(_checkLater.begin() + i);
		}
	}

	firstStrike();

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
	vector<Point> locs = this->getLocs();
	for (int i = 0; i < locs.size(); i++)
	{
		if (x == locs.at(i).x && y == locs.at(i).y)
		{
			locs.erase(locs.begin() + i);
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
	vector<Point> locs = this->getLocs();
	for (int i = locs.size() - 1; i >= 0; i--)
	{
		Point p = locs.at(i);
		if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
		{
			locs.erase(locs.begin() + i);
			_checkLater.push_back(p);
			//cout << "Removed " << p << endl;
		}
	}
}
void Enemy::firstStrike()	//gives info on what type of ship was hit
{
	//Loop through to find which ship was hit, sets the size needed to sink the ship
	Point hit = _hits.back();
	bool FoundShip = false;  
	Ship ship;

	for (int i = this->getShips().size()-1; i >= 0; i--)
	{
		ship = this->getShips().at(i);
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
				vector<Ship> ships = this->getShips();
				ships.erase(ships.begin() + i);

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
					cout << "The ship I am looking for is the " << ship.getShipName() << endl;
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
//create a new vector findShip that combines locs and checkLater, don't sort
//vector<Point> findShip = _locs;
//findShip.insert(findShip.end(), _checkLater.begin(), _checkLater.end());	
//concatenates _locs and _checkLater, index in for Loop corresponds
void Enemy::FindTheShip(int **temp, int board[])
{
	Point hit = _hits.back();	//returns the last Point in _hits
	//if hit is in one of the ships, get the ship name and size

	bool foundShip = false;

	int x = hit.x;
	int y = hit.y;

	//(a, y) (b, y) (x, c) (y, d)
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;
	
	for (int index = this->getShips().size() - 1; index >= 0; index--)
	{
		Point p = this->getLocs().at(index);
		if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
		{
			//cout << "I will check if there is a ship in _locs at: " << p <<endl;
			FocusedHitOrMiss(temp, board, index, p);
			foundShip = true;
			break;
		}
	}
	if (foundShip = false)	//check _checkLater if no match in _locs
	{
		for (int index = 0; index < _checkLater.size(); index++)
		{
			Point p = _checkLater.at(index);
			if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
			{
				cout << "I will check if there is a ship in _checkLater at: " << p << endl;
				FocusedHitOrMiss(temp, board, index, p);
				break;
			}
		}
	}
	
}

Point Enemy::getLastStrike()
{
	return _lastStrike;
}

void Enemy::Print()	//Prints the vectors _locs, _checkLater, and _hits for troubleshooting
{
	/*
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
	*/
}



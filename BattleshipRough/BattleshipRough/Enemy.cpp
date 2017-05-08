#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Enemy.h"


using namespace std;

Enemy::Enemy() : Board()
{
	//_locs;
	//_checkLater;
	//_hits;
	//_misses;
	_state = 0;
	_hitShips;
	_lastStrike;
	
	/////
	_lastHit;
	_ShipVectIndex;
}
Enemy::~Enemy()
{
	//
}
Enemy::Enemy(vector<Point> &locs, vector<Point> &checkLater, bool state, vector<Ship> &someShips) : Board()
{
	//_locs = locs;
	//_checkLater = checkLater;
	//_hits;
	//_misses;
	_state = state;
	//_someShips = someShips;	//when this is empty, win condition
	_hitShips;
	_lastStrike;

	///////
	//vector<Point> 
	_carrier;
	_battleship;
	_cruiser;
	_submarine;
	_destroyer;
	//vector< vector<Point> >
	_hits = { _carrier, _battleship, _cruiser, _submarine, _destroyer };
	_lastHit;
	_ShipVectIndex;
}

void Enemy::turn(Board &board)
{
	if (_state == 0)
	{
		RandomHitOrMiss(board.getTemp(), board);
	}
	else if (_state == 1)
	{
		FindTheShip(board.getTemp(), board);
	}
	Point ls = getLastStrike();
	vector<Point> points;
	if (board.getPointState(ls) == 1)
	{
		board.setPointState(ls, 9);
		/*
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
				vector<Ship> ships = board.getShips();
				Ship *ship = &ships[i];
				ship->setNoOfSpaces(ship->getNoOfSpaces() - 1);
				cout << "They hit your " << ship->getShipName() << " (" << ship->getNoOfSpaces() << " spaces left)" << endl;
				if (board.getShips()[i].getNoOfSpaces() == 0)
				{
					cout << "They've sunk your " << board.getShips()[i].getShipName() << "!" << endl;
					board.sunkenShips++;
				}
				board.setShips(ships);
			}
			isShip = false;
		}
		*/
	}
	else
		board.setPointState(ls, 5);
}


void Enemy::RandomHitOrMiss(int **temp, Board &board)
{
	int index = rand() % this->getLocs().size();

	Point p = this->getLocs().at(index);
	int x = p.x;	//row number
	int y = p.y;	//col number
	
	if (temp[x][y] == 1)
	{
		cout << p << endl;
		cout << "They guessed " << p << " -- HIT" << endl;
			//check if the ship has sunk
			//if not sunk, call function to look for ship
		Hit(index, p, board);
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

void Enemy::FocusedHitOrMiss(int **temp, int index, Point p, Board &board)
{
	int x = p.x;
	int y = p.y;

	if (temp[x][y] == 1)	//If ship is there
	{
		cout << "They guessed " << p << " -- FOCUSED HIT" << endl;
		Hit(index, p, board);
	}
	else
	{
		cout << "They guessed " << p << " -- FOCUSED MISS" << endl;
		Miss(index, p);
		//_state = 0;
	}
	_lastStrike = p;
}

void Enemy::Hit(int index, Point p, Board &board)
{
	//this->printHits();
	
	//vector<Point> hits = this->getHits();
	//hits.push_back(p);
	//this->setHits(hits);
	
	//this->printHits();

	//should call the draw function to change graphics of the board corresponding to HIT
	
	int x = p.x;
	int y = p.y;
	_lastHit = p;

	
	/*
	for (int i = 0; i < _checkLater.size(); i++)
	{
	if (x == _checkLater.at(i).x && y == _checkLater.at(i).y)
	{
	_checkLater.erase(_checkLater.begin() + i);
	}
	}
	*/

	firstStrike(board);	//will get appropriate _ShipVectIndex

	_hits[_ShipVectIndex].push_back(p);	//adds hit point to appropriate ship

	for (int i = 0; i < _locs.size(); i++)
	{
		if (x == _locs.at(i).x && y == _locs.at(i).y)
		{
			_locs.erase(_locs.begin() + i);
		}
	}
	Print();
}

void Enemy::Miss(int index, Point p)
{
	//removes the missed space from spaces to check permanently
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
	/*
	for (int i = 0; i < _checkLater.size(); i++)
	{
	if (x == _checkLater.at(i).x && y == _checkLater.at(i).y)
	{
	_checkLater.erase(_checkLater.begin() + i);
	}
	}
	*/
	Print();
}
/*
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
	vector<Point> checkLater = this->getCheckLater();
	for (int i = locs.size() - 1; i >= 0; i--)
	{
		Point p = locs.at(i);
		if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
		{
			locs.erase(locs.begin() + i);
			checkLater.push_back(p);
			//cout << "Removed " << p << endl;
		}
	}
	this->setLocs(locs);
	this->setCheckLater(checkLater);

}
*/


void Enemy::firstStrike(Board &board)	//gives info on what type of ship was hit
{
	//Loop through to find which ship was hit, sets the size needed to sink the ship
	
	//vector<Ship> ships = this->getShips();	//_someShips is now ships
	vector<Point> points;
	Point hit = _lastHit;


	for (int i = 0; i < board.getShips().size(); i++)
	{
		points = board.getShips()[i].getPoints();

		for (int j = 0; j < points.size(); j++)
		{
			Point p = points.at(j);

			if (p.x == hit.x && p.y == hit.y)
			{
				vector<Ship> ships = board.getShips();
				Ship *ship = &ships[i];
				ship->setNoOfSpaces(ship->getNoOfSpaces() - 1);

				cout << "They hit your " << ship->getShipName() << " (" << ship->getNoOfSpaces() << " spaces left)" << endl;
				
				_ShipVectIndex = i;
				board.setShips(ships);

				if (board.getShips()[i].getNoOfSpaces() == 0)
				{
					cout << "They've sunk your " << ship->getShipName() << "!" << endl;
					board.sunkenShips++;
					_state = 0;
					break;
				}
				
			}		
		}
	}
}


/*
void Enemy::checkForHitShips()
{
	Ship ship = ships.at(0);
	for (int i = 0; i < ships.size(); i++)
	{
		ship = ships.at(i);
		if (ship.getIsNotHit() == false)	//false means it is hit
		{
			_lastHit = _hits[i].back();
			_state = 1;
			break;
		}
		else
		{
			_state = 0;
		}
	}
}
*/

//create a new vector findShip that combines locs and checkLater, don't sort
//vector<Point> findShip = _locs;
//findShip.insert(findShip.end(), _checkLater.begin(), _checkLater.end());	
//concatenates _locs and _checkLater, index in for Loop corresponds
void Enemy::FindTheShip(int **temp, Board &board)
{
	Point hit = _lastHit;	//returns the last Point in _hits
	int x = hit.x;
	int y = hit.y;
	vector<Point> currentShip = _hits[_ShipVectIndex];	//the vector of points corresponding to the ship comp is trying to find
	
	bool vertical = true;

	//(a, y) (b, y) (x, c) (x, d)
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int count = 0;

	if (currentShip.size() < 2)	//first hit
	{
		a = x - 1;
		b = x + 1;
		c = y - 1;
		d = y + 1;

		for (int index = 0; index < _locs.size(); index++)
		{
			Point p = _locs.at(index);
			if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
			{
				//cout << "I will check if there is a ship in _locs at: " << p << endl;
				FocusedHitOrMiss(temp, index, p, board);
				//foundShip = true;
				count++;
				break;
			}
		}
		//if no match was found
		if (count == 0)
		{
			_state = 0;
			//RandomHitOrMiss(temp, board);
			cout << "error, no match 1" << endl;

		}
	}
	else if (currentShip.size() >= 2 && x == currentShip.end()[-2].x)	//if greater than or equal to 2 and vertical, y is rows, x is cols
	{
		vertical = true;
		c = findMin(currentShip, vertical) - 1;
		d = findMax(currentShip, vertical) + 1;
		//cout << "Is vertical. Check y coordinates " << c << " and " << d << " at x coordinate " << x << endl;
		for (int index = 0; index < _locs.size(); index++)
		{
			Point p = _locs.at(index);
			if ((p.x == x && p.y == c) || (p.x == x && p.y == d))
			{
				//cout << "I will check if there is a ship in _locs at: " << p << endl;
				FocusedHitOrMiss(temp, index, p, board);
				count++;
				break;
			}

		}
		if (count == 0)
		{
			_state = 0;
			cout << "error, no match 2" << endl;
		}
	}
	else if (currentShip.size() >= 2 && y == currentShip.end()[-2].y)	//if greater than or equal to 2 and horizontal
	{
		vertical = false;
		a = findMin(currentShip, vertical) - 1;
		b = findMax(currentShip, vertical) + 1;
		//cout << "Is horizontal. Check x coordinates " << a << " and " << b << " at y coordinate " << y << endl;
		for (int index = 0; index < _locs.size(); index++)
		{
			Point p = _locs.at(index);
			if ((p.x == a && p.y == y) || (p.x == b && p.y == y))
			{
				//cout << "I will check if there is a ship in _locs at: " << p << endl;
				FocusedHitOrMiss(temp, index, p, board);
				count++;
				break;
			}
		}
		
		if (count == 0)
		{
			_state = 0;
			cout << "error, no match 3" << endl;
		}
	}
	//cannot find point in _locs
	else
	{
		_state = 0;
		RandomHitOrMiss(temp, board);
	}
}
int Enemy::findMin(vector<Point> &currentShip, bool vertical)
{
	int min = 0;
	if (vertical == true)
	{
		min = currentShip[0].y;
		for (int i = 1; i < currentShip.size(); i++)
		{
			if (currentShip[i].y <= min)
				min = currentShip[i].y;
		}
	}
	else
	{
		min = currentShip[0].x;
		for (int i = 1; i < currentShip.size(); i++)
		{
			if (currentShip[i].x <= min)
				min = currentShip[i].x;
		}
	}
	//cout << "The current ship size is " << currentShip.size() << " and min is " << min << endl;
	return min;
}
int Enemy::findMax(vector<Point> &currentShip, bool vertical)
{
	int max = 0;
	if (vertical == true)
	{
		max = currentShip[0].y;
		for (int i = 1; i < currentShip.size(); i++)
		{
			if (currentShip[i].y >= max)
				max = currentShip[i].y;
		}
	}
	else
	{
		max = currentShip[0].x;
		for (int i = 1; i < currentShip.size(); i++)
		{
			if (currentShip[i].x >= max)
				max = currentShip[i].x;
		}
	}
	//cout << "The current ship size is " << currentShip.size() << " and max is " << max << endl;
	return max;
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



#include <iostream>
#include<random>
#include<vector>
#include<string>
#include<algorithm>
#include"Enemy.h"
#include"Point.h"
#include"PlaceShip.h"
#include"Ship.h"
#include"Board.h"

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
Enemy::Enemy(vector<Point> &locs, vector<Point> &checkLater, bool state, vector<Ship> &someShips)
{
	_locs = locs;
	_checkLater = checkLater;
	_state = state;
	_someShips = someShips;	//when this is empty, win condition

	//vector<Point> 
	_carrier;
	_battleship;
	_cruiser;
	_submarine;
	_destroyer;
	//vector< vector<Point> >
	_hits = { _carrier, _battleship, _cruiser, _submarine, _destroyer };

	//used during program, empty right now
	_misses;
	_hitShips;

	_ShipVectIndex = 0;

	_lastHit;
	_lastStrike;
	_win = false;
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
		cout << p << " is a HIT" << endl;
			//check if the ship has sunk
			//if not sunk, call function to look for ship
		Hit(index, p);
		_state = 1;
	}

	else
	{
		cout << p << " is a MISS" << endl;
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
		cout << " is a HIT." << endl;
		Hit(index, p);
	}
	else
	{
		cout << " is a MISS." << endl;
		Miss(index, p);
	}
	_lastStrike = p;
}

void Enemy::Hit(int index, Point p)
{
	//Remove p from locations to check (_locs)
	int x = p.x;
	int y = p.y;
	_lastHit = p;

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

	firstStrike();	//will get appropriate _ShipVectIndex
	_hits[_ShipVectIndex].push_back(p);	//adds hit point to appropriate ship

	Print();
	cout << endl;
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

//removeAdjSpaces is bugging out the system, 
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
*/

void Enemy::firstStrike()	//gives info on what type of ship was hit
{
	//Loop through to find which ship was hit, sets the size needed to sink the ship
	Point hit = _lastHit;
	cout << "_lastHit = " << hit <<endl;

	//bool FoundShip = false;  
	Ship ship = _someShips.at(0);	//initialize the pointer to a ship
	

	for (int i = 0; i <_someShips.size(); i++)
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
				

				_ShipVectIndex = i;
				ship.setNoOfSpaces(ship.getNoOfSpaces() - 1);
				ship.setIsNotHit(false);
				cout << "IsNotHit is " << ship.getIsNotHit() << endl;

				//replace old ship with new ship without changing order
				_someShips.erase(_someShips.begin() + i);
				_someShips.insert(_someShips.begin() + i, ship);

				//_hitShips.push_back(ship);	//adds ship with new size to _hitShips;
				//_someShips.erase(_someShips.begin() + i);	//should set value to zero, not remove...
				ship = _someShips[i];

				cout << "The size of this ship is now " << ship.getNoOfSpaces() << endl;

				if (ship.getNoOfSpaces() == 0)
				{
					cout << "The " << ship.getShipName() << " has been sunk!" << endl;
					ship.setIsNotHit(true);	//sets it back to true, don't try to sink anymore
					
					//replace old ship with new ship without changing order
					_someShips.erase(_someShips.begin() + i);
					_someShips.insert(_someShips.begin() + i, ship);

					//check win condition

					checkForHitShips();
					//_state = 0;
					break;
				}
				
			}
		}
	}
	/*
	if (FoundShip == false)
	{
		for (int i = 0; i < _hitShips.size(); i++)
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
					
					_ShipVectIndex = i;
					ship.setNoOfSpaces(ship.getNoOfSpaces() - 1);	//change the size of the ship
					_hitShips.erase(_hitShips.begin() + i); //remove ship with old size
					_hitShips.push_back(ship);	//add ship with new size

					cout << "The size of this ship is now " << ship.getNoOfSpaces() << endl;
					FoundShip = true;
					if (ship.getNoOfSpaces() == 0)
					{
						cout << "The " << ship.getShipName() << " has been sunk!" << endl;
						//remove all coordinates from _hits
						//RemoveHits(ship);
						_hitShips.erase(_hitShips.begin() + i);
						if (_hitShips.size() == 0)
							_state = 0;
						//else statement to get previous hit, figure out algorithm
						
						break;
					}
				}
			}
		}
	}
	*/
}
void Enemy:: checkForHitShips()
{
	Ship ship = _someShips.at(0);
	for (int i = 0; i < _someShips.size(); i++)
	{
		ship = _someShips.at(i);
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

/*
void Enemy::RemoveHits(Ship ship)
{
	vector<Point> coord = ship.getPoints();

	for (int j = coord.size() - 1; j >= 0; j--)
	{
		Point p = coord.at(j);

		for (int k = 0; k < _hits.size(); k++)
		{
			Point phits = _hits.at(k);
			if(p.x == phits.x && p.y == phits.y)
			{
				_hits.erase(_hits.begin() + k);
			}
		}
	}
}
*/

void Enemy::FindTheShip(int **temp, int board[])
{
	Point hit = _lastHit;	//returns the last Point in _hits
	vector<Point> currentShip = _hits[_ShipVectIndex];	//the vector of points corresponding to the ship comp is trying to find
	
	bool foundShip = false;
	bool vertical = true;

	int x = hit.x;
	int y = hit.y;

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
			if ( (p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d) )
			{
				cout << "I will check if there is a ship in _locs at: " << p << endl;
				FocusedHitOrMiss(temp, board, index, p);
				//foundShip = true;
				count++;
				break;
			}
		}
		//check _checkLater if no match in _locs
		/*
		if (foundShip = false)	
		{
			for (int index = _checkLater.size() - 1; index >= 0; index--)
			{
				cout << "Check in _checkLater" << endl;
				Point p = _checkLater.at(index);
				if ((p.x == a && p.y == y) || (p.x == b && p.y == y) || (p.x == x && p.y == c) || (p.x == x && p.y == d))
				{
					cout << "I will check if there is a ship in _checkLater at: " << p << endl;
					FocusedHitOrMiss(temp, board, index, p);
					break;
				}
			}
		}
		*/
		//if no match was found
		if(count == 0)
		{
			_state = 0;
			//RandomHitOrMiss(temp, board);
			cout << "error, no match 1" << endl;

		}
	}
	else if (currentShip.size() >= 2 && x == currentShip.end()[-2].x)	//if greater than or equal to 2 and vertical! y is rows, x is cols
	{
		vertical = true;
		c = findMin(currentShip, vertical) - 1;
		d = findMax(currentShip, vertical) + 1;
		cout << "Is vertical. Check y coordinates " << c << " and " << d << " at x coordinate "<< x <<endl;
		for (int index = 0; index < _locs.size(); index++)
		{
			Point p = _locs.at(index);
			if ((p.x == x && p.y == c) || (p.x == x && p.y == d))
			{
				cout << "I will check if there is a ship in _locs at: " << p << endl;
				FocusedHitOrMiss(temp, board, index, p);
				count++;
				break;
			}
			
		}
		//check _checkLater if no match in _locs
		/*
		if (foundShip = false)	
		{
			for (int index = _checkLater.size() - 1; index >= 0; index--)
			{
				Point p = _checkLater.at(index);
				if ((p.x == x && p.y == c) || (p.x == x && p.y == d))
				{
					cout << "I will check if there is a ship in _checkLater at: " << p << endl;
					FocusedHitOrMiss(temp, board, index, p);
					break;
				}
			}
		}
		*/
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
		cout << "Is horizontal. Check x coordinates " << a << " and " << b <<" at y coordinate "<< y << endl;
		for (int index = 0; index < _locs.size(); index++)
		{
			Point p = _locs.at(index);
			if ((p.x == a && p.y == y) || (p.x == b && p.y == y))
			{
				cout << "I will check if there is a ship in _locs at: " << p << endl;
				FocusedHitOrMiss(temp, board, index, p);
				count++;
				break;
			}
			
		}
		//check _checkLater if no match in _locs
		/*
		if (foundShip = false)	
		{
			for (int index = _checkLater.size() - 1; index >= 0; index--)
			{
				Point p = _checkLater.at(index);
				if ((p.x == a && p.y == y) || (p.x == b && p.y == y))
				{
					cout << "I will check if there is a ship in _checkLater at: " << p << endl;
					FocusedHitOrMiss(temp, board, index, p);
					break;
				}
			}
		}
		*/
		if (count == 0)
		{
			_state = 0;
			cout << "error, no match 3" << endl;
			//RandomHitOrMiss(temp, board);
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
	cout << "The current ship size is " << currentShip.size() << " and min is " << min << endl;
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
	cout << "The current ship size is " << currentShip.size() << " and max is " << max << endl;
	return max;
}
bool Enemy::WinCondition()
{
	if (_someShips.size() == 0)
	{
		_win = true;
		cout << "COMP WINS!" << endl;
	}
	return _win;
	
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
	*/
	//checkLater
	/*
	cout << "_checkLater contains "<<endl;
	for (int i = 0; i < _checkLater.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _checkLater.at(i) << "   ";
	}
	cout << endl;
	*/
	cout << "_hits contains "<<endl;
	for (int i = 0; i < _hits.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		for (int j = 0; j < _hits[i].size(); j++)
		{
			cout << _hits[i].at(j) << "   ";
		}
		cout << endl;
	}
	cout << "_misses now contains " << endl;
	cout << _misses.at(_misses.size() - 1) << endl;
	/*
	for (int i = 0; i < _misses.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << _misses.at(i) << "   ";
	}
	cout << endl;
	*/
}



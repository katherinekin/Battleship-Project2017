#include "Player.h"

Player::Player() : Board()
{
	//rewrite the vector statements
	// _locs;
	//_hits;
	//_misses;

}

Player::~Player()
{
}

Player::Player(vector<Point>& locs, vector<Ship>& someShips) : Board()
{
	// _locs = locs;
	//_hits;
	//_misses;
	//_someShips = someShips;	//when this is empty, win condition
	_hitShips;
	_lastStrike;
}


void Player::turn(int ** temp, int board[], Board enemyBoard)
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
			cout << "You guessed " << p << " -- HIT" << endl;
			Hit(p);
		}
		else
		{
			cout << "You guessed " << p << " -- MISS" << endl;
			Miss(p);
		}
	}
	Point ls = getLastStrike();
	vector<Point> points;
	if (temp[ls.x][ls.y] == 1)	// Point State reference:
	{
		enemyBoard.setPointState(ls, 9);	// 0:= Empty; 1:= Ship Occupant; 5:= Missed; 9:= Hit
		
		vector<Ship> theirShips = enemyBoard.getShips();
		cout << enemyBoard.getShips().size() << endl;
		cout << theirShips.size() << endl;
		cout << this->getShips().size() << endl;
		cout << "Can't seem to get these to work. Player.cpp" << endl;
		system("pause");
		
		bool isShip = false;
		for (int i = 0; i < enemyBoard.getShips().size(); i++)
		{
			points = theirShips[i].getPoints();
			for (int j = 0; j < points.size(); j++)
			{
				if (ls.x == points[j].x && ls.y == points[j].y)
				{
					isShip = true;
				}
			}
			if (isShip == true) 
			{
				theirShips[i].setNoOfSpaces(theirShips[i].getNoOfSpaces() - 1);
				cout << "You hit their " << theirShips[i].getShipName() << " (" << theirShips[i].getNoOfSpaces() << " spaces left)" << endl;
				if (theirShips[i].getNoOfSpaces() == 0)
				{
					cout << "You've sunk their " << theirShips[i].getShipName() << "!" << endl;
					for (int z = 0; z < theirShips.size(); z++)
						cout << theirShips[z].getShipName() << " " << theirShips[z].getNoOfSpaces() << endl;
				}
			}
			isShip = false;
		}
	}
	else if (enemyBoard.getPointState(ls) == 9 || enemyBoard.getPointState(ls) == 5)
	{
		// Do nothing.
	}
	else
		enemyBoard.setPointState(ls, 5);
}

void Player::turn(Board &board)
{
	Point p;
	p.userAssigned();
	system("cls");
	int ** temp = board.getTemp();
	if (temp[p.x][p.y] != 1 && temp[p.x][p.y] != 0)
		cout << "You already tried that space. You lose your turn." << endl;
	else
	{
		if (temp[p.x][p.y] == 1)
		{
			cout << "You guessed " << p << " -- HIT" << endl;
			Hit(p);
		}
		else
		{
			cout << "You guessed " << p << " -- MISS" << endl;
			Miss(p);
		}
	}
	_lastStrike = p;
	Point ls = getLastStrike();
	vector<Point> points;
	vector<Ship> ships;
	if (board.getPointState(ls) == 1)	// Point State reference:
	{
		board.setPointState(ls, 9);	// 0:= Empty; 1:= Ship Occupant; 5:= Missed; 9:= Hit
		bool isShip = false;
		ships = board.getShips();
		for (int i = 0; i < ships.size(); i++)
		{
			points = ships[i].getPoints();
			for (int j = 0; j < points.size(); j++)
			{
				if (ls.x == points[j].x && ls.y == points[j].y)
				{
					isShip = true;
				}
			}
			if (isShip == true) 
			{
				ships[i].setNoOfSpaces(ships[i].getNoOfSpaces() - 1);
				cout << "You hit their " << ships[i].getShipName() << " (" << ships[i].getNoOfSpaces() << " spaces left)" << endl;
				board.setShips(ships);
				//board.printShips();
				if (ships[i].getNoOfSpaces() == 0)
				{
					cout << "You've sunk their " << ships[i].getShipName() << "!" << endl;
					// add to sunkenShip
				}
			}
			isShip = false;
		}
	}
	else if (board.getPointState(ls) == 9 || board.getPointState(ls) == 5)
	{
		// Do nothing.
	}
	else
		board.setPointState(ls, 5);
}



void Player::Hit(Point p)
{
	this->getHits().push_back(p);
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
	this->setLocs(locs);
}

void Player::Miss(Point p)
{
	//removes the missed space from spaces to check permanently
	//check if p is in _locs or _checkLater before deleting
	int x = p.x;
	int y = p.y;

	vector<Point> misses = this->getMisses();
	misses.push_back(p);
	this->setMisses(misses);
	vector<Point> locs = this->getLocs();
	for (int i = 0; i < locs.size(); i++)
	{
		if (x == locs.at(i).x && y == locs.at(i).y)
			locs.erase(locs.begin() + i);
	}
	this->setLocs(locs);
}
/*
vector<Point> Player::getHits()
{
	return _hits;
}
*/


Point Player::getLastStrike()
{
	return _lastStrike;
}

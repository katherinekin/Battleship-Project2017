#include "Player.h"

Player::Player() : Board()
{
	//rewrite the vector statements
	// _locs;
	_hits;
	_misses;

}

Player::~Player()
{
}

Player::Player(vector<Point>& locs, vector<Ship>& someShips) : Board()
{
	// _locs = locs;
	_hits;
	_misses;
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
	_lastStrike = p;
	Point ls = _lastStrike;
	vector<Point> points;
	if (temp[ls.x][ls.y] == 1)	// Point State reference:
	{
		enemyBoard.setPointState(ls, 9);	// 0:= Empty; 1:= Ship Occupant; 5:= Missed; 9:= Hit
		
		
		vector<Ship> theirShips = enemyBoard.getShips();
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
/*
void Player::turn(Enemy board)
{
	Point p;
	p.userAssigned();
	system("cls");
	int ** temp = this->getTemp();
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
	if (board.getPointState(ls) == 1)	// Point State reference:
	{
		board.setPointState(ls, 9);	// 0:= Empty; 1:= Ship Occupant; 5:= Missed; 9:= Hit
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
				cout << "You hit their " << board.getShips()[i].getShipName() << " (" << board.getShips()[i].getNoOfSpaces() << " spaces left)" << endl;
				vector<Ship> ships = board.getShips();
				vector<Ship> ships2 = getShips();
				if (board.getShips()[i].getNoOfSpaces() == 0)
				{
					cout << "You've sunk their " << board.getShips()[i].getShipName() << "!" << endl;
					enemySunken++;
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
*/


void Player::Hit(Point p)
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
}

void Player::Miss(Point p)
{
	//removes the missed space from spaces to check permanently
	//check if p is in _locs or _checkLater before deleting
	int x = p.x;
	int y = p.y;

	_misses.push_back(p);
	for (int i = 0; i < this->getLocs().size(); i++)
	{
		if (x == this->getLocs().at(i).x && y == this->getLocs().at(i).y)
		{
			vector<Point> a = this->getLocs();
			a.erase(a.begin() + i);
		}

	}

}

vector<Point> Player::getHits()
{
	return _hits;
}



Point Player::getLastStrike()
{
	return _lastStrike;
}


#include "Board.h"
#include <iostream>


using namespace std;

const int ROW = 10;

Board::Board()
{
	sunkenShips = 0;
	_boardArray = new int[ROW*ROW];
	_temp = new int*[ROW];
	//_state = 0;
	_cpuPlayer = false;

	for (int r = 0; r < ROW; r++)
	{
		_temp[r] = &_boardArray[r*ROW];
	}

	//set values for board
	for (int i = 0; i < ROW*ROW; i++)
	{
		_boardArray[i] = 0;
	}
	int count = 0;
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < ROW; c++)
		{
			_locs.at(count).x = r;	//<==
			_locs.at(count).y = c;
			count++;
		}
	}
}


Board::~Board()
{
	//Destructor	
}

void Board::setCpuPlayer(bool cpuPlayer)
{
	_cpuPlayer = cpuPlayer;
}

bool Board::getCpuPlayer()
{
	return _cpuPlayer;
}

void Board::setPointState(Point p, int state)
{
	_temp[p.x][p.y] = state;	//<==
}

int Board::getPointState(Point p)
{
	int state = _temp[p.x][p.y];	//<==
	return state;
}

void Board::printPointVector(vector<Point> points)
{
	for (int i = 0; i < points.size(); i++)
		cout << points[i] << " ";
	cout << endl;
}

vector<Point> Board::getLocs()
{
	return _locs;
}

void Board::printLocs()
{
	printPointVector(_locs);
}

vector<Point> Board::getCheckLater()
{
	return _checkLater;
}

void Board::printCheckLater()
{
	cout << "Check Later: ";
	printPointVector(_checkLater);
}

void Board::setLocs(vector<Point> locs)
{
	_locs = locs;
}

void Board::setCheckLater(vector<Point> checkLater)
{
	_checkLater = checkLater;
}

int * Board::getBoardArray()
{
	return _boardArray;
}

void Board::setBoardArray(int * boardArray)
{
	_boardArray = boardArray;
}

int ** Board::getTemp()
{
	return _temp;
}
/*
void Board::setState(bool state)
{
	_state = state;
}

bool Board::getState()
{
	return _state;
}
*/
bool Board::addShip(Ship s)
{
	vector<Point> tempPoints = s.getPoints();
	// Check if any point the ship will occupy is already occupied
	for (int i = 0; i < s.getNoOfSpaces(); i++)
	{
		Point tempPoint = tempPoints[i];
		if (_temp[tempPoint.x][tempPoint.y] > 0)	//<==
		{
			return false;
		}
	}
	// Add the ship object to the temp 2-D array, return true
	for (int i = 0; i < s.getNoOfSpaces(); i++)
	{
		Point tempPoint = tempPoints[i];
		this->setPointState(tempPoint, 1);
	}
	_ships.push_back(s);
	return true;
}

void Board::addShips(vector<Ship> ships)
{
	_ships = ships;
}

void Board::setShips(vector<Ship> ships)
{
	_ships = ships;
}

vector<Ship> Board::getShips()
{
	return _ships;
}

void Board::printShips()
{
	Ship temp;
	cout << "Printing Ships: " << endl;
	for (int i = 0; i < _ships.size(); i++)
	{
		temp = _ships[i];
		cout << temp.getShipName() << " ";
		printPointVector(temp.getPoints());
		cout << '(' << temp.getNoOfSpaces() << ')';
		cout << endl;
	}
}

vector<Point> Board::getHits()
{
	return _hits;
}

void Board::setHits(vector<Point> hits)
{
	_hits = hits;
}

void Board::printHits()
{
	cout << "HITS: ";
	printPointVector(_hits);
}

vector<Point> Board::getMisses()
{
	return _misses;
}

void Board::setMisses(vector<Point> misses)
{
	_misses = misses;
}

void Board::printMisses()
{
	cout << "MISSES: ";
	printPointVector(_misses);
}

void Board::setTemp(int ** temp)
{
	_temp = temp;
}

ostream & operator<<(ostream & os, const Board board)
{
	// Margin Row
	os << endl;
	// Letter Row
	char colLetter = 'A';
	os << "     ";
	for (int x = 0; x < 10; x++)
	{
		os << colLetter << "   ";
		colLetter++;
	}
	os << endl;
	// Top Line
	os << "   _";
	for (int c = 0; c < 10; c++)
		os << "____";
	os << endl;
	int count = 0;
	for (int r = 0; r < ROW; r++)
	{
		// Padding Line
		os << "   |  ";
		for (int c = 0; c < 10; c++)
			os << " |  ";
		os << endl;
		if ((r + 1) < 10)
			os << " " << (r + 1) << " | ";
		else
			os << " " << (r + 1) << "| ";

		for (int c = 0; c < ROW; c++)
		{
			// Data Line
			if (board._cpuPlayer == false)
			{
				switch (board._temp[c][r])	//<==x is now columns, y rows
				{
				case 0:
					os << "  | ";
					break;
				case 1:
					os << char(178) << " | ";
					break;
				case 5:
					os << "O | ";
					break;
				case 9:
					os << "X | ";
					break;
				default:
					os << "ERRR";
					break;
				}
			}
			else
			{
				switch (board._temp[c][r]) {	//<==
				case 0:
					os << "  | ";
					break;
				case 1:
					os << "  | ";
					break;
				case 5:
					os << "O | ";
					break;
				case 9:
					os << "X | ";
					break;
				default:
					os << "ERRR";
					break;
				}
			}
		}
		os << endl;
		os << "   |";
		for (int c = 0; c < 10; c++)
			os << "___|";
		os << endl;
	}
	return os;
}

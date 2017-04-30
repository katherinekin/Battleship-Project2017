#include "Board.h"
#include <iostream>


using namespace std;

const int ROW = 10;

Board::Board()
{
	
	_boardArray = new int[ROW*ROW];
	_temp = new int*[ROW];
	_state = 0;

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
			_locs.at(count).x = r;
			_locs.at(count).y = c;
			count++;
		}
	}
}

Board::~Board()
{
	//Destructor	
}

void Board::setPointState(Point p, int state)
{
	_temp[p.x][p.y] = state;
}

int Board::getPointState(Point p)
{
	int state = _temp[p.x][p.y];
	return state;
}

vector<Point> Board::getLocs()
{
	return _locs;
}

vector<Point> Board::getCheckLater()
{
	return _checkLater;
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

void Board::setState(bool state)
{
	_state = state;
}

bool Board::getState()
{
	return _state;
}

bool Board::addShip(Ship s)
{
	// Check if any point the ship will occupy is already occupied
	// OR if the ship runs off the board, return false
	// Add the ship object to the temp 2-D array, return true
	return false;
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
			os << board._temp[r][c] << " | ";
		}
		os << endl;
		os << "   |";
		for (int c = 0; c < 10; c++)
			os << "___|";
		os << endl;
	}
	return os;
}
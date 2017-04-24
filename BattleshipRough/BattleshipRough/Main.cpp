#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Enemy.h"

using namespace std;

//>>>>>>> 569c42c630e8af973fb93b5cda905329246abdd5
//void HitOrMiss(int **temp, int board[], vector<Point> &locs, vector<Point> &checkLater);
//void removeAdjSpaces(vector<Point> &locs, int x, int y, vector<Point> &checkLater);
//void findtheShip(vector<Point> &locs, int x, int y, vector<Point> &checkLater);
//void Miss(vector<Point> &locs, int i, Point p, vector<Point> &checkLater);

int main()
{
	// sample code for constructing and printing a point
	Point samplePoint(2, 2);
	cout << samplePoint << endl << endl;

	int row = 10;
	int* board = new int[row*row];
	int** temp = new int*[row];
	vector<Point> locs(100);
	vector<Point> checkLater;
	bool state = 0;
	

	for (int r = 0; r < row; r++)
	{
		temp[r] = &board[r*row];
	}

	//set values for board
	for (int i = 0; i < row*row; i++)
	{
		board[i] = 0;
	}

	//set some of the values to 1 (arbitrary ships)
	temp[1][0] = 1;
	temp[1][1] = 1;
	temp[1][2] = 1;

	//draw the board
	//set vector locs
	
	// Margin Row
	cout << endl;

	// Letter Row
	char colLetter = 'A';
	cout << "     ";
	for (int x = 0; x < 10; x++)
	{
		cout << colLetter << "   ";
		colLetter++;
	}
	cout << endl;

	// Top Line
	cout << "   _";
	for (int c = 0; c < 10; c++)
		cout << "____";
	cout << endl;

	int count = 0;
	for (int r = 0; r < row; r++)
	{
		// Padding Line
		cout << "   |  ";
		for (int c = 0; c < 10; c++)
			cout << " |  ";
		cout << endl;
		if ((r+1) < 10)
			cout << " " << (r+1) << " | ";
		else
			cout << " " << (r+1) << "| ";

		for (int c = 0; c < row; c++)
		{		
			locs.at(count).x = r;
			locs.at(count).y = c;
			count++;

			//draw

			// cout << temp[r][c] << " ";
			
			// Data Line
			cout << temp[r][c] <<" | ";

		}
		cout << endl;
		cout << "   |";
		for (int c = 0; c < 10; c++)
			cout << "___|";
		cout << endl;
	}

	//initialize comp
	Enemy comp(locs, checkLater, state);

	//computer keeps going until player exits or types 'Q'
	char userInput;
	cout << "Press enter to allow the computer to move" << endl;
	cin.get(userInput);

	while (!(userInput == 'Q'))
	{
		comp.turn(temp, board);
		cin.get(userInput);
	} 

	return 0;
}

/*
void HitOrMiss(int **temp, int board[], vector<Point> &locs, vector<Point> &checkLater)
{
	int index = rand() % locs.size();
	Point p = locs.at(index);
	int x = p.x;
	int y = p.y;

	if (temp[x][y] == 1)
	{
		cout << x << ", " << y << endl;
		cout << "HIT"<<endl;
		//check if the ship has sunk
		//if not sunk, call function to look for ship
	}
	else
	{
		cout << x << ", " << y << endl;
		cout << "MISS"<<endl;
		
		//write this in a new function, that calls adjacent spaces
		Miss(locs, index, p, checkLater);
	}
	

	for (int i = 0; i < locs.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << locs.at(i) <<"   ";
	}

	cout << endl;
	for (int i = 0; i < checkLater.size(); i++)
	{
		//cout << "My vector contains " << locs.at(i);
		cout << checkLater.at(i) << "   ";
	}
	cout << endl;
}

void Miss(vector<Point> &locs, int index, Point p, vector<Point> &checkLater)
{	
	locs.erase(locs.begin() + index);
	//call function to also remove adjacent spaces
	removeAdjSpaces(locs, p.x, p.y, checkLater);
	cout << p.x << ", " << p.y << " is a miss!" << endl;
}


//remove the missed space and the adjacent spaces, called by hit or miss
void removeAdjSpaces(vector<Point> &locs, int x, int y, vector<Point> &checkLater)
{
	
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	//if a, b, c, d are <0 or >9, will not be removed
	//(a, y) (b, y) (x, c) (y, d)
	//need to place in another vector for potential spaces to check, shouldn't remove
	//counting backwards to avoid missing spaces...works!
	for (int i = locs.size()-1; i >= 0; i--)
	{
		Point p = locs.at(i);
		//check edge cases
		if(p.x == a && p.y == y)
		{
			locs.erase(locs.begin() + i);
			checkLater.push_back(p);
			cout << "Removed " << p.x << ", " << p.y << endl;
		}
		if(p.x == b && p.y == y)
		{
			locs.erase(locs.begin() + i);
			checkLater.push_back(p);
			cout << "Removed " << p.x << ", " << p.y << endl;
		}
		if(p.x == x && p.y == c)
		{
			locs.erase(locs.begin() + i);
			checkLater.push_back(p);
			cout << "Removed " << p.x << ", " << p.y << endl;
		}
		if(p.x == x && p.y == d)
		{
			locs.erase(locs.begin() + i);
			checkLater.push_back(p);
			cout << "Removed " << p.x << ", " << p.y << endl;
		}
	}
}
void findtheShip(vector<Point> &loc, int x, int y, vector<Point> &checkLater)
{
	//if hit, look for the ship
	//cin.get()
	int a = x - 1;
	int b = x + 1;
	int c = y - 1;
	int d = y + 1;

	char q;
	while (!(q = 'Q'))
	{
		//
	}

}

*/
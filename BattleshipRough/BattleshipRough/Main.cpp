#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Enemy.h"

//>>>>>>> 569c42c630e8af973fb93b5cda905329246abdd5

int main()
{
	// sample code for constructing and printing a point
//<<<<<<< HEAD
	Point samplePoint(2, 2);
	cout << samplePoint << endl << endl;


//>>>>>>> 569c42c630e8af973fb93b5cda905329246abdd5
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

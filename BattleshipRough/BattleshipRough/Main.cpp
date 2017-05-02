#include <iostream>
#include<random>
#include<vector>
#include<string>
#include"Enemy.h"
//<<<<<<< HEAD
#include "Board.h"
#include "Ship.h"
//=======

using namespace std;

//>>>>>>> Katherine2
//>>>>>>> 569c42c630e8af973fb93b5cda905329246abdd5
void splashScreen();

int main()
{
//<<<<<<< HEAD
	Board sampleBoard = Board();
//=======
	// sample code for constructing and printing a point
//<<<<<<< HEAD
	Point samplePoint(2, 2);
	Point testPoint(2, 2);
	//if (testPoint == samplePoint)
		//cout << "True!"<<endl;


//>>>>>>> 569c42c630e8af973fb93b5cda905329246abdd5
	int row = 10;
	int* board = new int[row*row];
	int** temp = new int*[row];
	vector<Point> locs(100);
	vector<Point> checkLater;
	
//>>>>>>> Katherine2
	
	/*
	Point a = Point(1, 0);
	Point b = Point(1, 1);
	Point c = Point(1, 2);
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	sampleBoard.setPointState(a, 1);
	sampleBoard.setPointState(b, 1);
	sampleBoard.setPointState(c, 1);
	*/

	splashScreen();
	bool run = true;
	while (run) 
	{
		cout << sampleBoard;
		Ship sampleShip = Ship(4, "Battleship", 'b');
		if (sampleBoard.addShip(sampleShip) == true)
			run = false;
	}

	run = true;
	while (run)
	{
		cout << sampleBoard;
		Ship sampleShip2 = Ship(5, "Carrier", 'c');
		if (sampleBoard.addShip(sampleShip2) == true)
		{
			
			run = false;
		}
	}
	cout << sampleBoard;

	bool state = 0;

	//initialize comp
	//Enemy comp(locs, checkLater, state);
	Enemy comp(sampleBoard.getLocs(), sampleBoard.getCheckLater(), state);
	//computer keeps going until player exits or types 'Q'
	char userInput;
	cout << "Press enter to allow the computer to move" << endl;
	cin.get(userInput);

	//can change to win condition
	while (!(userInput == 'Q'))
	{
		//comp.turn(temp, board);
		comp.turn(sampleBoard.getTemp(), sampleBoard.getBoardArray());
		
		cout << "Press enter to allow the computer to move" << endl;
		cin.get(userInput);
	} 

	return 0;
}

void splashScreen()
{
	cout << "    ____        __  __  __          __    _     " << endl;
	cout << "   / __ )____ _/ /_/ /_/ /__  _____/ /_  (_)___ " << endl;
	cout << "  / __  / __ `/ __/ __/ / _ \\/ ___/ __ \\/ / __ \\" << endl;
	cout << " / /_/ / /_/ / /_/ /_/ /  __(__  ) / / / / /_/ /" << endl;
	cout << "/_____/\\__,_/\\__/\\__/_/\\___/____/_/ /_/_/ .___/ " << endl;
	cout << "                                       /_/      " << endl << endl;
	cout << "By Jaylon Dukes, Katherine Kin, and Payne Wheat" << endl << endl;
	cout << "COSC 1430 - Dr. Dursun" << endl << endl;
	cout << "For the best experience, maximize your console window." << endl << endl;
	system("pause");
	system("cls");
}
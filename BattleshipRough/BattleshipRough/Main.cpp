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
void shipAddition(Board board, int spaces, string name);

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
/*
	int row = 10;
	int* board = new int[row*row];
	int** temp = new int*[row];
	vector<Point> locs(100);
	vector<Point> checkLater;
*/
// Code no longer necessary.
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
	shipAddition(sampleBoard, 5, "Carrier");
	shipAddition(sampleBoard, 4, "Battleship");
	shipAddition(sampleBoard, 3, "Cruiser");
	shipAddition(sampleBoard, 3, "Submarine");
	shipAddition(sampleBoard, 2, "Destroyer");

	/*
	while (run)
	{
		cout << sampleBoard;
		Ship sampleShip2 = Ship(5, "Carrier");
		if (sampleBoard.addShip(sampleShip2) == true)
			run = false;
	}
	run = true;
	while (run)
	{
		cout << sampleBoard;
		Ship sampleShip = Ship(4, "Battleship");
		if (sampleBoard.addShip(sampleShip) == true)
			run = false;
	}
	*/
	cout << sampleBoard;

	bool state = 0;

	//initialize comp
	//Enemy comp(locs, checkLater, state);
	Enemy comp(sampleBoard.getLocs(), sampleBoard.getCheckLater(), state);
	//computer keeps going until player exits or types 'Q'
	char userInput;
	cout << "Press enter to allow the computer to move" << endl;
	cin.get(userInput);
	system("cls");

	Point ls;

	//can change to win condition
	while (!(userInput == 'Q'))
	{
		cin.clear();
		//cin.ignore();
		//comp.turn(temp, board);
		comp.turn(sampleBoard.getTemp(), sampleBoard.getBoardArray());
		ls = comp.getLastStrike();
		if (sampleBoard.getPointState(ls) == 1)
			sampleBoard.setPointState(ls, 9);
		else
			sampleBoard.setPointState(ls, 5);
		cout << sampleBoard;
		cout << "Press enter to allow the computer to move" << endl;
		cin.get(userInput);
		system("cls");

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

void shipAddition(Board board, int spaces, string name)
{
	bool run = true;
	cout << board;
	while (run)
	{
		Ship sampleShip2 = Ship(spaces, name);
		if (board.addShip(sampleShip2) == true)
			run = false;
		else
		{
			system("cls");
			cout << board;
			cout << "A ship already occupies one or more of those spaces!" << endl << "Try Again." << endl;
		}
	}
}

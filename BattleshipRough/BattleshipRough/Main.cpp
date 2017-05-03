#include <iostream>
#include<random>
#include<vector>
#include<string>
#include <ctime>
#include"Enemy.h"
//<<<<<<< HEAD
#include "Board.h"
#include "Ship.h"
//=======

using namespace std;

//>>>>>>> Katherine2
//>>>>>>> 569c42c630e8af973fb93b5cda905329246abdd5
void splashScreen();
void shipAddition(Board board, int spaces, string name, bool randomPlacement);

int main()
{
	srand(time(0)); // makes everything more randomer
//<<<<<<< HEAD
	Board sampleBoard = Board();
//=======
	// sample code for constructing and printing a point
//<<<<<<< HEAD
	Point samplePoint(2, 2);
	Point testPoint(2, 2);
	//if (testPoint == samplePoint)
		//cout << "True!"<<endl;

	splashScreen();

	shipAddition(sampleBoard, 5, "Carrier", true);
	shipAddition(sampleBoard, 4, "Battleship", true);
	shipAddition(sampleBoard, 3, "Cruiser", true);
	shipAddition(sampleBoard, 3, "Submarine", true);
	shipAddition(sampleBoard, 2, "Destroyer", true);

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
		//comp.turn(temp, board);
		comp.turn(sampleBoard.getTemp(), sampleBoard.getBoardArray());
		ls = comp.getLastStrike();
		if (sampleBoard.getPointState(ls) == 1)	// Point State reference:
			sampleBoard.setPointState(ls, 9);	// 0:= Empty; 1:= Ship Occupant; 5:= Missed; 9:= Hit
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
	system("cls");
	bool run = true;
	bool randomPlacement;
	cout << board;
	cout << "Manually place " << name << " or Randomly? M/R: ";
	string ui;
	cin >> ui;
	if (ui[0] == 'M' || ui[0] == 'm') 
		randomPlacement = false;
	else if (ui[0] == 'R' || ui[0] == 'r')
		randomPlacement = true;

	while (run)
	{
		Ship ship = Ship(spaces, name, randomPlacement, 100);
		if (board.addShip(ship) == true)
			run = false;
		else
		{
			cout << board;
			cout << "A ship already occupies one or more of those spaces!" << endl << "Try Again." << endl << endl;
		}
	}
}
void shipAddition(Board board, int spaces, string name, bool randomPlacement)
{
	system("cls");
	bool run = true;
	cout << board;
	while (run)
	{
		Ship ship = Ship(spaces, name, randomPlacement, 100);
		if (board.addShip(ship) == true)
			run = false;
		else
		{
			cout << board;
			cout << "A ship already occupies one or more of those spaces!" << endl << "Try Again." << endl << endl;
		}
	}
}
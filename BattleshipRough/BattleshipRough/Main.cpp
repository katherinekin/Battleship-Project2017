#include <iostream>
#include<random>
#include<vector>
#include<array>
#include<string>
#include <ctime>
#include"Enemy.h"
#include "Board.h"
#include "Ship.h"
#include"PlaceShip.h"


using namespace std;

void splashScreen();	//splashScreen for the game
vector<Ship> RandomBoard(Board board);	//Makes a board with randomly placed ships for the computer

int main()
{
	srand(time(0)); // makes everything more randomer

	Board sampleBoard = Board();

	splashScreen();
	vector<Ship> myShips;
	myShips = RandomBoard(sampleBoard);

	bool state = 0;

	//Enemy comp(locs, checkLater, state);
	Enemy comp(sampleBoard.getLocs(), sampleBoard.getCheckLater(), state, myShips);	//initialize comp

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
		else if(sampleBoard.getPointState(ls) == 0)
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

//can be used to generate board for the player and the computer
//returns a vector of liveships
vector<Ship> RandomBoard(Board sampleBoard)
{
	int ShipSize[5] = { 5, 4, 3, 3, 2 };
	string ShipName[5] = { "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" };
	PlaceShip someShips;
	
	//make a vector of ships
	//each ship should contain a vector of points
	
	for(int i = 0; i<5; i++)
	{
		someShips.shipAddition(sampleBoard, ShipSize[i], ShipName[i], true);
	}
	return someShips.getLiveShips();
}
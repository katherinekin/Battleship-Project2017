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
#include "Player.h"

using namespace std;

int splashScreen();	//splashScreen for the game
vector<Ship> RandomBoard(Board board);	//Makes a board with randomly placed ships for the computer
vector<Ship> ManualBoard(Board board);

int main()
{
	srand(time(0)); // makes everything more randomer

	Board sampleBoard = Board();
	Board enemyBoard = Board();
	vector<Ship> myShips;
	vector<Ship> theirShips;
	//enemyBoard.setCpuPlayer(true); //this line sets the board to only display hits and misses.
	int option = splashScreen();
	string ui = "";
	if (option == 1)
	{
		myShips = ManualBoard(sampleBoard);
	}
	else if (option == 2)
	{
		myShips = RandomBoard(sampleBoard);
	}
	cin.clear();
	cin.ignore();
	system("cls");
	cout << sampleBoard;
	cout << endl << "Your board has been set." << endl;
	theirShips = RandomBoard(enemyBoard);
	cout << "The Enemy's board has been set." << endl;
	//system("pause");

	bool state = 0;

	//Enemy comp(locs, checkLater, state);
	Enemy comp(sampleBoard.getLocs(), sampleBoard.getCheckLater(), state, myShips);	//initialize comp
	Player player(enemyBoard.getLocs(), myShips);
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
		cout << "Press enter to begin your move" << endl;
		cin.get(userInput);
		system("cls");
		cout << enemyBoard << endl;
		player.turn(enemyBoard.getTemp(), enemyBoard.getBoardArray());
		ls = player.getLastStrike();
		if (enemyBoard.getPointState(ls) == 1)	// Point State reference:
			enemyBoard.setPointState(ls, 9);	// 0:= Empty; 1:= Ship Occupant; 5:= Missed; 9:= Hit
		else
			enemyBoard.setPointState(ls, 5);
		cout << enemyBoard;
		cin.clear();
		cin.ignore();
		cout << "Press enter to allow the computer to move" << endl;
		cin.get(userInput);
		system("cls");
	} 

	return 0;
}

int splashScreen()
{
	cout << "    ____        __  __  __          __    _     " << endl;
	cout << "   / __ )____ _/ /_/ /_/ /__  _____/ /_  (_)___ " << endl;
	cout << "  / __  / __ `/ __/ __/ / _ \\/ ___/ __ \\/ / __ \\" << endl;
	cout << " / /_/ / /_/ / /_/ /_/ /  __(__  ) / / / / /_/ /" << endl;
	cout << "/_____/\\__,_/\\__/\\__/_/\\___/____/_/ /_/_/ .___/ " << endl;
	cout << "                                       /_/      " << endl << endl;
	cout << "By Jaylon Dukes, Katherine Kin, and Payne Wheat" << endl << endl;
	cout << "COSC 1430 - Dr. Dursun" << endl << endl;
	cout << "For the best experience, maximize your console window." << endl << endl << endl;
	cout << "Select Option:" << endl;
	cout << "1. Manually Assign Ship Locations" << endl;
	cout << "2. Randomly Assign Ship Locations" << endl;
	string ui;
	bool run = true;
	while (run)
	{
		cin >> ui;
		if (ui[0] == '1')
		{
			cin.clear();
			return 1;
		}
		else if (ui[0] == '2')
		{
			cin.clear();
			return 2;
		}
		else
			cout << "Input error. Try again: ";
		cin.clear();
	}
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
vector<Ship> ManualBoard(Board sampleBoard)
{
	int ShipSize[5] = { 5, 4, 3, 3, 2 };
	string ShipName[5] = { "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" };
	PlaceShip someShips;
	for (int i = 0; i<5; i++)
	{
		someShips.shipAddition(sampleBoard, ShipSize[i], ShipName[i]);
	}
	return someShips.getLiveShips();
}
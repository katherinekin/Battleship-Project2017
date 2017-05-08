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
	
	//tests to check Point::isEqualTo() function
	/*
	cout << "Testing isEqualTo() member function of Point class:" << endl;
	
	Point a = Point(1, 1);
	Point b = Point(1, 1);
	Point c = Point(1, 2);
	Point d = Point(2, 1);
	Point e = Point(5, 8);

	
	cout << "Is " << a << " equal to " << b << "? " << a.isEqualTo(b) << endl; // should be true
	cout << "Is " << a << " equal to " << c << "? " << a.isEqualTo(c) << endl; // false
	cout << "Is " << a << " equal to " << d << "? " << a.isEqualTo(d) << endl; // false
	cout << "Is " << a << " equal to " << e << "? " << a.isEqualTo(e) << endl; // false
	system("pause");
	system("cls");
	*/

	// Initialize Boards
	Player playerBoard = Player();
	Enemy enemyBoard = Enemy();
	
	// Initialize Ship vectors
	vector<Ship> myShips;
	vector<Ship> theirShips;
	//enemyBoard.setCpuPlayer(true); //this line sets the board to only display hits and misses.

	// Take input from Splash Screen and set board pieces
	int option = splashScreen();
	cin.clear();
	cin.ignore();
	if (option == 1)
		myShips = ManualBoard(playerBoard);
	else if (option == 2)
		myShips = RandomBoard(playerBoard);

	system("cls");

	theirShips = RandomBoard(enemyBoard);
	enemyBoard.addShips(theirShips);
	enemyBoard.printShips();
	
	cout << "The Enemy's board has been set." << endl;

	playerBoard.addShips(myShips);
	playerBoard.printShips();
	cout << playerBoard;
	cout << endl << "Your board has been set." << endl;

	//system("pause");

	bool state = 0;

	//computer keeps going until player exits or types 'Q'
	char userInput;
	cout << "Press enter to allow the computer to move" << endl;
	cin.get(userInput);
	system("cls");
	int enemySunken = 0;
	int playerSunken = 0;
	Point ls;

	//can change to win condition
	while (!(userInput == 'Q'))
	{
		cin.clear();
		if (enemySunken == theirShips.size())
		{
			cout << "YOU WIN!" << endl;
			system("pause");
			break;
		}
		//comp.turn(temp, board);	
		//comp.turn(playerBoard.getTemp(), playerBoard.getBoardArray());

		enemyBoard.turn(playerBoard);
		playerBoard.printShips();

		if (playerBoard.sunkenShips == myShips.size())
		{
			cout << "YOU LOSE." << endl;
			system("pause");
			break;
		}
		cout << playerBoard;
		cout << "Press enter to begin your move" << endl;
		cin.get(userInput);
		system("cls");

		cout << "YOUR MOVE" << endl;
		cout << enemyBoard << endl;
		//playerBoard.turn(enemyBoard.getTemp(), enemyBoard.getBoardArray(), enemyBoard);

		//Player's turn (comment out to troubleshoot CPU)
		playerBoard.turn(enemyBoard);
		cout << enemyBoard;
		enemyBoard.printShips();
		//

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
	cout << endl;
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
	return 0;
}


//can be used to generate board for the player and the computer
//returns a vector of liveships
vector<Ship> RandomBoard(Board board)
{
	int ShipSize[5] = { 5, 4, 3, 3, 2 };
	string ShipName[5] = { "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" };
	PlaceShip someShips;
	
	//make a vector of ships
	//each ship should contain a vector of points
	
	for(int i = 0; i<5; i++)
	{
		someShips.shipAddition(board, ShipSize[i], ShipName[i], true);
	}
	return someShips.getLiveShips();
}
vector<Ship> ManualBoard(Board board)
{
	int ShipSize[5] = { 5, 4, 3, 3, 2 };
	string ShipName[5] = { "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" };
	PlaceShip someShips;
	for (int i = 0; i<5; i++)
	{
		someShips.shipAddition(board, ShipSize[i], ShipName[i]);
	}
	return someShips.getLiveShips();
}
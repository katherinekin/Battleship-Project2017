#include"PlaceShip.h"


PlaceShip::PlaceShip() : Ship()
{
	_board;
	_spaces = 0;
	_name = "";
	_randomPlacement = true;
	_LiveShips;

}
PlaceShip::~PlaceShip(){}
/*
PlaceShip::PlaceShip(Board board, int spaces, string name, bool randomPlacement)
{
	_board = board;
	_spaces = spaces;
	_name = name;
	_randomPlacement = randomPlacement;
	_LiveShips;

}
*/
//manual placement of ships
void PlaceShip::shipAddition(Board board, int spaces, string name)
{
	system("cls");
	bool run = true;
	bool _randomPlacement;
	cout << board;
	cout << "Manually place " << name << " or Randomly? M/R: ";
	string ui;
	cin >> ui;
	if (ui[0] == 'M' || ui[0] == 'm')
		_randomPlacement = false;
	else if (ui[0] == 'R' || ui[0] == 'r')
		_randomPlacement = true;

	while (run)
	{
		Ship ship = Ship(spaces, name, _randomPlacement, 100);
		if (board.addShip(ship) == true)
		{
			_LiveShips.push_back(ship);
			run = false;
		}
		else
		{
			cout << board;
			cout << "A ship already occupies one or more of those spaces!" << endl << "Try Again." << endl << endl;
		}
	}
}
 
//random placement of ships
void PlaceShip::shipAddition(Board board, int spaces, string name, bool randomPlacement)
{
	//system("cls");
	bool run = true;
	//cout << board;

	while (run)
	{
		Ship ship = Ship(spaces, name, randomPlacement, 100);
		if (board.addShip(ship) == true)
		{
			_LiveShips.push_back(ship);
			run = false;
		}
			
		/*
		else
		{
			cout << board;
			cout << "A ship already occupies one or more of those spaces!" << endl << "Try Again." << endl << endl;
		}
		*/
	}
	
}
vector<Ship> PlaceShip::getLiveShips()
{
	return _LiveShips;
}
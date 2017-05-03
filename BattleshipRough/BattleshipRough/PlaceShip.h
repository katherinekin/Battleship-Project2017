#ifndef PLACESHIP_H
#define PLACESHIP_H
#include"Board.h"
#include"Ship.h"
#include<vector>

class PlaceShip : public Ship
{
public:
	PlaceShip();
	~PlaceShip();
	//PlaceShip(Board board, int spaces, string name, bool randomPlacement);

	void shipAddition(Board board, int spaces, string name);
	void shipAddition(Board board, int spaces, string name, bool randomPlacement);
	vector<Ship> getLiveShips();
private:
	Board _board;
	int _spaces;
	string _name;
	bool _randomPlacement;
	vector<Ship> _LiveShips;
};
#endif //PLACESHIP_H
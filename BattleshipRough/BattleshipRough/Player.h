#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>

using namespace std;

class Player
{
public:
	void turn()
	{
		cout << "Please enter a coordinate" << endl;
		cin >> _a;
		cout << "You picked " << _a << endl;
	}
	void setA()
	{
		_a = 0;
	}
	int getA()
	{
		return _a;
	}
private:
	int _a = 0;
};
#endif //PLAYER_H


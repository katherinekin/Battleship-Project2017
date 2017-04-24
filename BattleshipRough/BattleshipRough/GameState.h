#ifndef GAMESTATE_H
#define GAMESTATE_H
#include<random>

//if player has already had a turn, computer should go
//if computer goes, player should go
class Gamestate
{
public:
	void ChangeState(int state, int a, int b)
	{
		_state = state;
		if (_state == 0)
			_state = 1;
		if (_state == 1)
			_state = 0;
	}
	void setState() {}
	int getState()
	{
		return _state;
	}
private:
	int _state = rand() % 1;
};
#endif // !GAMESTATE_H
#pragma once

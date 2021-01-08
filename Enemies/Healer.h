#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"

class Healer : public Enemy
{
private:
	bool isForward;

public:
	Healer(int id, int arrTime, double health, double power, int RL, int speed);

	void Act(Enemy * enemy, int currTimeStep);

	void Move();

	bool Freezed();

	bool Killed();

	~Healer(void);
};


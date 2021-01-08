#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"
class Freezer : public Enemy
{
public:
	Freezer(int id, int arrTime, double health, double power, int RL, int speed);

	void Act(Castle * castle, int currTimeStep);

	void Move();

	bool Freezed();

	bool Killed();

	~Freezer(void);
};


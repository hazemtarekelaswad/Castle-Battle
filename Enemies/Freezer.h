#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"
class Freezer : public Enemy
{
public:
	Freezer(int id, int arrTime, double health, double power, int RL, int speed);

	void Active(Castle * C);

	void Move();

	bool Freezed();

	bool Killed();

	~Freezer(void);
};


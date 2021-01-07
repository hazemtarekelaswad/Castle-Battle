#pragma once
#include "Enemies/Enemy.h"
#include "Castle/Castle.h"

class Healer : public Enemy
{
public:
	Healer(int id, int arrTime, double health, double power, int RL, int speed);

	void Active(Castle * C);

	void Move();

	bool Freezed();

	bool Killed();

	~Healer(void);
};


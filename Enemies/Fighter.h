#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"
class Fighter : public Enemy
{
	GUI* pGUI;
	int priFactor;

public:
	Fighter(int id,int arrTime, double health, double power, int RL, int speed);

	void Act(Castle* castle, int currTimeStep);

	void Move() override;

	int GetPriFactor() const;

	~Fighter(void);
};


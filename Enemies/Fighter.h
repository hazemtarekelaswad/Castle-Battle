#pragma once
#include "Enemies/Enemy.h"
#include "Castle/Castle.h"
class Fighter : public Enemy
{
	GUI* pGUI;

public:
	Fighter(int id,int arrTime, double health, double power, int RL, int speed);

	void Act();

	void Move();

	~Fighter(void);
};


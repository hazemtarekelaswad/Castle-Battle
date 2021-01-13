#include "Freezer.h"
#include "../Defs.h"

Freezer::Freezer(int id, int arrTime, double health, double power, int RL, int speed) 
	: Enemy (id, arrTime, FREEZER, health, power, RL, speed)
{
}

void Freezer :: Act(Castle * castle, int currTimeStep)
{
	if ((currTimeStep - ArrvTime) % ReloadTime + 1)		// to check if the freezer is at reload period
		return;

	if (status == ACTV) {}
		// Formulate an equation for freezing the castle
}

void Freezer :: Move()
{
	if (status == ACTV)
		MoveForward();

}

bool Freezer :: Freezed()
{

}

bool Freezer :: Killed()
{

}

Freezer::~Freezer(void)
{
}

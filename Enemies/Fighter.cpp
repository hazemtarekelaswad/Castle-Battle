#include "Fighter.h"
#include "../Defs.h"


Fighter::Fighter(int id, int arrTime, double health, double power, int RL, int speed) 
	: Enemy (id, arrTime, FIGHTER, health, power, RL, speed)   
{
}

void Fighter :: Act(Castle* castle, int currTimeStep)
{
	if ((currTimeStep - ArrvTime) % ReloadTime + 1)		// to check if the fighter is at reload period in order not to act
		return;

	if (status == ACTV)
		castle->SetHealth(castle->GetHealth() - ((Health < 0.5 * OrgHealth ? 0.5 : 1) / Distance) * Power);
}

void Fighter :: Move()
{
	if (status == ACTV)
		MoveForward();
}



Fighter::~Fighter(void)
{
}

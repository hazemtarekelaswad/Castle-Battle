#include "Fighter.h"
#include "../Defs.h"


Fighter::Fighter(int id, int arrTime, double health, double power, int RL, int speed) 
	: Enemy (id, arrTime, FIGHTER, health, power, RL, speed)   
{
}

void Fighter :: Act()
{

}

void Fighter :: Move()
{
	if (status == ACTV)
		SetDistance(Distance - (Health < 0.5 * OrgHealth ? 0.5 * Speed : Speed));
}



Fighter::~Fighter(void)
{
}

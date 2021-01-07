#include "Freezer.h"
#include "../Defs.h"

Freezer::Freezer(int id, int arrTime, double health, double power, int RL, int speed) 
	: Enemy (id, arrTime, FREEZER, health, power, RL, speed)
{
}

void Freezer :: Active(Castle * C)
{

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

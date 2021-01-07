#include "Healer.h"
#include "../Defs.h"

Healer::Healer(int id, int arrTime, double health, double power, int RL, int speed) 
	: Enemy (id, arrTime, HEALER, health, power, RL, speed), isForward(true)
{
}

void Healer :: Active(Castle * C)
{

}

void Healer :: Move()
{

	if (status == ACTV) {
		if (Distance == MinDistance)
			isForward = false;
		else if (Distance == MaxDistance)
			isForward = true;

		if (isForward)
			MoveForward();
		else
			SetDistance(Distance + (Health < 0.5 * OrgHealth ? 0.5 * Speed : Speed)); // Move Backward
	}

}

bool Healer :: Freezed()
{

}

bool Healer :: Killed()
{

}

Healer::~Healer(void)
{
}

#include "Healer.h"
#include "Defs.h"

Healer::Healer(int id, int arrTime, double health, double power, int RL, int speed) : Enemy (id, arrTime, HEALER, health, power, RL, speed)
{
}

void Healer :: Active(Castle * C)
{

}

void Healer :: Move()
{


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

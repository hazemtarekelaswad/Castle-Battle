#include "Freezer.h"
#include "Defs.h"

Freezer::Freezer(int id, int arrTime, double health, double power, int RL, int speed) : Enemy (id, arrTime, HEALER, health, power, RL, speed)
{
}

void Freezer :: Active(Castle * C)
{

}

void Freezer :: Move()
{


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

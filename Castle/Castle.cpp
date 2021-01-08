#include "Castle.h"

Castle::Castle() {
}

Castle::Castle(double h, int n, double p) : MaxEnemies(n) {
	SetHealth(n);
	SetPower(p);
}



void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}
void Castle::SetMaxEnemies(int n) {
	MaxEnemies = n;
}

void Castle::SetPower(double p) {
	Power = p;
}


double Castle::GetHealth() const
{
	return Health;
}
int Castle::GetMaxEnemies() const {
	return MaxEnemies;
}
double Castle::GetPower() const {
	return Power;
}
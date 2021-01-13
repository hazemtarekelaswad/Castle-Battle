#include "Castle.h"

Castle::Castle(double h, int n, double p, double th) 
	: MaxEnemies(n), Threshold(th), IceAmount(0) {
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

void Castle::SetThreshold(double th) {
	Threshold = th;
}

void Castle::SetStatus(CSL_STATUS stat) {
	status = stat;
}
void Castle::SetIceAmount(int amount) {
	IceAmount = amount;
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
double Castle::GetThreshold() const {
	return Threshold;
}
CSL_STATUS Castle::GetStatus() const {
	return status;
}
int Castle::GetIceAmount() const {
	return IceAmount;
}
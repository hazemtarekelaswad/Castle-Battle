#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	int MaxEnemies;		// the maximum number of enemies a castle can attack at any time step
	double Power;

public:
	Castle();
	Castle(double h, int n, double p);

	void SetHealth(double h);
	void SetMaxEnemies(int n);
	void SetPower(double p);

	double GetHealth() const;
	int GetMaxEnemies() const;
	double GetPower() const;

	void Act();

};


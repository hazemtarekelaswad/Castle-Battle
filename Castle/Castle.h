#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	int MaxEnemies;		// the maximum number of enemies a castle can attack at any time step
	double Power;
	double Threshold;
	CSL_STATUS status;
	double IceAmount;

public:
	Castle(double h, int n, double p, double th);

	void SetHealth(double h);
	void SetMaxEnemies(int n);
	void SetPower(double p);
	void SetThreshold(double th);
	void SetStatus(CSL_STATUS stat);
	void SetIceAmount(double amount);

	double GetHealth() const;
	int GetMaxEnemies() const;
	double GetPower() const;
	double GetThreshold() const;
	CSL_STATUS GetStatus() const;
	double GetIceAmount() const;

	void Act();

};


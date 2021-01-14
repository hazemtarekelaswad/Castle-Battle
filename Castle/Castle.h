#pragma once
#include "..\Defs.h"
#include "..\Generic_DS\PrtQueue.h"
#include "..\Generic_DS\Stack.h"
#include "..\Generic_DS\Queue.h"
#include "..\Enemies\Fighter.h"
#include "..\Enemies\Healer.h"
#include "..\Enemies\Freezer.h"

class Castle
{
	double Health;
	int MaxEnemies;		// the maximum number of enemies a castle can attack at any time step
	double Power;
	double Threshold;
	CSL_STATUS status;
	double IceAmount;

public:
	Castle();
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

	void ShootBullets(PrtQueue<Fighter*>& fightersQ, Stack<Healer*>& healersStack, Queue<Freezer*>& freezersQ, int currTimeStep);

	void ShootIce(PrtQueue<Fighter*>& fightersQ, Stack<Healer*>& healersStack, Queue<Freezer*>& freezersQ, int currTimeStep);
};


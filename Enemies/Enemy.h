#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	GUI* pGUI;

	const int ID;  //Each enemy has a unique ID (sequence number)
	
	const int ArrvTime;	//arrival time (time it starts to join battle)

	ENMY_STATUS status;	    //status of the enemy (inactive, active, frosted, killed)
	
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health

	double OrgHealth; // Enemy health at the start of the game

	double Speed;
	
	double Power;

	int FreezeTime;

	int ReloadTime;

	int FirstShotDelay;
	
	int FirstShotTime;
	
	int KillDelay;
	
	int LifeTime;
	
	int EnemyKilledTime;
	
	int N; // No. of Enemies to be served by the castle

	ENMY_TYPE Enemy_Type; // Type of the enemy (Fighter, Healer, Freezer)

	float K; // Factor constant in the equations
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	Enemy(int id, int arrTime, ENMY_TYPE type, double H, double P, int RL, double s);

	virtual ~Enemy();

	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();

	void SetDistance(int );

	void SetHealth(double H);

	void SetSpeed(double s);

	void SetPower(double P);

	void SetReloadTime(int RL);

	void SetFirstShotDelay(int FSD);

	void SetKillDelay(int KD);

	void SetLifeTime(int LT);

	void SetEnemyKilledTime(int KT);

	void SetFirstShotTime(int FST);
// -----------------------------------------------------------
	int GetDistance() const;
	
	int GetArrvTime() const;
	
	double GetHealth() const;
	
	double GetSpeed() const;
	
	double GetPower() const;

	int GetReloadTime() const;
    
	int GetFirstShotDelay() const;
	
	int GetKillDelay() const;
	
	int GetLifeTime() const;
	
	int GetEnemyKilledTime() const;
	
	int GetFirstShotTime() const;

	int GetID() const;
	
	ENMY_STATUS GetStatus() const;
	// Virtual Functions: ----------------

	//virtual void Move();	//All enemies can move
	//virtual void Act();	//Acting means fighting or healing
	
	//
	// TODO: Add More Member Functions As Needed
	//

	bool Freezed();

	bool Killed();

};


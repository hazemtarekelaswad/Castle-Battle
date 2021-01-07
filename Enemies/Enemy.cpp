#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, int d) : ID(id),ArrvTime(arrTime)
{   
	SetDistance(d);
}

Enemy :: Enemy (int id, int arrTime, ENMY_TYPE type, double H, double P, int RL, double s)  
	: ID(id), ArrvTime(arrTime), OrgHealth(Health)
{
	Enemy_Type = type;
	SetHealth (H);
	SetPower(P);
	SetReloadTime(RL);
	SetSpeed(s);

	FirstShotDelay = 0;
	KillDelay = 0;
	LifeTime = 0;
	EnemyKilledTime = 0;
}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d < MinDistance)
		Distance = MinDistance;
	else if (d > MaxDistance)
		Distance = MaxDistance;
	else
		Distance = d;
}



int Enemy::GetDistance() const
{
	return Distance;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

void Enemy :: SetHealth(double H)
{
	Health = H;
}


void Enemy ::  SetSpeed(double s)
{ 
	if (s > 0)
		Speed = s;

	else 
		Speed = 0;
}
void Enemy ::  SetPower(double P)
{
	if (P > 0)
	Power = P;

	else 
		Power = 0;
}

void Enemy :: SetReloadTime(int RL)
{
	if (RL > 0)
	ReloadTime = RL;

	else 
		ReloadTime = 0;
}

void Enemy :: SetFirstShotDelay(int FSD)
{
	if (FSD > 0)
	FirstShotDelay = FSD;

	else 
		FirstShotDelay = 0;
}

void Enemy :: SetKillDelay(int KD)
{
	if (KD > 0)
	KillDelay = KD;

	else 
		KillDelay = 0;
}
void Enemy :: SetLifeTime(int LT)
{
	if (LT > 0)
	LifeTime = LT;

	else 
		LifeTime = 0;
}

void Enemy :: SetEnemyKilledTime(int KT)
{
	if (KT > 0)
	EnemyKilledTime = KT;

	else 
		EnemyKilledTime =0;

}

void Enemy :: SetFirstShotTime(int FST)
{
	FirstShotTime = FST;
}

double Enemy :: GetHealth () const
{
	return Health;
}

double Enemy :: GetSpeed() const
{
	return Speed;
}

double Enemy :: GetPower() const
{
	return Power;
}

int Enemy ::  GetReloadTime() const
{
	return ReloadTime;
}

int Enemy :: GetFirstShotDelay() const
{
	return FirstShotDelay;
}

int Enemy :: GetKillDelay() const
{
	return KillDelay;
}

int Enemy :: GetLifeTime() const
{
	return LifeTime;
}

int Enemy :: GetEnemyKilledTime() const
{
	return EnemyKilledTime;
}

int Enemy ::  GetFirstShotTime() const
{
	return FirstShotTime;
}

bool Enemy :: Freezed()
{
	if (FreezeTime > 0 || GetStatus() == FRST)
		return true;
	return false;
}

bool Enemy :: Killed()
{
	if (Health <= 0)
		return true;
	return false;
}

void Enemy::MoveForward() {
	SetDistance(Distance - (Health < 0.5 * OrgHealth ? 0.5 * Speed : Speed));
}
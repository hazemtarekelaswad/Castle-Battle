#include "Castle.h"
#include<ctime>

Castle::Castle() {}

Castle::Castle(double h, int n, double p, double th)
	: MaxEnemies(n), Threshold(th), IceAmount(0), FirstFreezeStep(0), OrgHealth(h)
{
	SetHealth(h);
	SetPower(p);
}

double Castle::GetOrgHealth() const {
	return OrgHealth;
}

void Castle::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}
void Castle::SetMaxEnemies(int n) {
	if (n > 0)
		MaxEnemies = n;
	else
		MaxEnemies = 0;
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
void Castle::SetIceAmount(double amount) {
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
double Castle::GetIceAmount() const {
	return IceAmount;
}

void Castle::Act(PrtQueue<Fighter*>& fightersQ, Stack<Healer*>& healersStack, Queue<Freezer*>& freezersQ, int currTimeStep) {
	srand(time(NULL));
	if(rand() % 5 == 0)
		ShootIce(fightersQ, healersStack, freezersQ, currTimeStep);
	else
		ShootBullets(fightersQ, healersStack, freezersQ, currTimeStep);
}

void Castle::ShootBullets(PrtQueue<Fighter*>& fightersQ, Stack<Healer*>& healersStack, Queue<Freezer*>& freezersQ, int currTimeStep) {

	if (status == CSL_FRST)
		return;

	Queue<Fighter*> tempFighters;
	Stack<Healer*> tempHealers;
	Queue<Freezer*> tempFreezers;

	for (int i = 0; i < MaxEnemies; ++i) {
		if (!fightersQ.isEmpty()) {
			Fighter* fighterPtr;
			fightersQ.dequeue(fighterPtr);
			fighterPtr->SetHealth(fighterPtr->GetHealth() - (Power / fighterPtr->GetDistance()));
			tempFighters.enqueue(fighterPtr);

			if (fighterPtr->GetFirstShotTime() == -1) {
				fighterPtr->SetFirstShotTime(currTimeStep);
				fighterPtr->SetFirstShotDelay(currTimeStep - fighterPtr->GetArrvTime());
			}

			if (fighterPtr->GetHealth() == 0) {
				fighterPtr->SetEnemyKilledTime(currTimeStep);
				fighterPtr->SetKillDelay(currTimeStep - fighterPtr->GetFirstShotTime());
			}
		}
		else if (!healersStack.isEmpty()) {
			Healer* healerPtr;
			healersStack.pop(healerPtr);
			healerPtr->SetHealth(healerPtr->GetHealth() - (0.5 * Power / healerPtr->GetDistance()));
			if (healerPtr->GetDistance() <= 5 && healerPtr->GetHealth() == 0)
				Health *= 1.03;
			tempHealers.push(healerPtr);

			if (healerPtr->GetFirstShotTime() == -1) {
				healerPtr->SetFirstShotTime(currTimeStep);
				healerPtr->SetFirstShotDelay(currTimeStep - healerPtr->GetArrvTime());
			}

			if (healerPtr->GetHealth() == 0) {
				healerPtr->SetEnemyKilledTime(currTimeStep);
				healerPtr->SetKillDelay(currTimeStep - healerPtr->GetFirstShotTime());
			}
		}
		else if (!freezersQ.isEmpty()) {
			Freezer* freezerPtr;
			freezersQ.dequeue(freezerPtr);
			freezerPtr->SetHealth(freezerPtr->GetHealth() - (Power / freezerPtr->GetDistance()));
			tempFreezers.enqueue(freezerPtr);

			if (freezerPtr->GetFirstShotTime() == -1) {
				freezerPtr->SetFirstShotTime(currTimeStep);
				freezerPtr->SetFirstShotDelay(currTimeStep - freezerPtr->GetArrvTime());
			}

			if (freezerPtr->GetHealth() == 0) {
				freezerPtr->SetEnemyKilledTime(currTimeStep);
				freezerPtr->SetKillDelay(currTimeStep - freezerPtr->GetFirstShotTime());
			}
		}
		else
			break;
	}


	for (int i = 0; i < MaxEnemies; ++i) {
		if (!tempFighters.isEmpty()) {
			Fighter* ptr;
			tempFighters.dequeue(ptr);
			fightersQ.enqueuePriority(ptr->GetPriFactor(), ptr);
		}
		else if (!tempHealers.isEmpty()) {
			Healer* healerPtr;
			tempHealers.pop(healerPtr);
			healersStack.push(healerPtr);
		}
		else if (!tempFreezers.isEmpty()) {
			Freezer* freezerPtr;
			tempFreezers.dequeue(freezerPtr);
			freezersQ.enqueue(freezerPtr);
		}
		else
			break;
	}
}

void Castle::ShootIce(PrtQueue<Fighter*>& fightersQ, Stack<Healer*>& healersStack, Queue<Freezer*>& freezersQ, int currTimeStep) {

	if (status == CSL_FRST)
		return;

	Queue<Fighter*> tempFighters;
	Stack<Healer*> tempHealers;
	Queue<Freezer*> tempFreezers;

	for (int i = 0; i < MaxEnemies; ++i) {
		if (!fightersQ.isEmpty()) {

			Fighter* fighterPtr;
			fightersQ.dequeue(fighterPtr);              
			tempFighters.enqueue(fighterPtr);

			if (fighterPtr->GetStatus() != FRST) {
				fighterPtr->SetStatus(FRST);
				fighterPtr->SetFrstTimeFrosted(currTimeStep);
			}
				
			if (fighterPtr->GetFirstShotTime() == -1) {
				fighterPtr->SetFirstShotTime(currTimeStep);
				fighterPtr->SetFirstShotDelay(currTimeStep - fighterPtr->GetArrvTime());
			}
		}
		else if (!healersStack.isEmpty()) {
			Healer* healerPtr;
			healersStack.pop(healerPtr);
			tempHealers.push(healerPtr);


			if (healerPtr->GetStatus() != FRST) {
				healerPtr->SetStatus(FRST);
				healerPtr->SetFrstTimeFrosted(currTimeStep);
			}


			if (healerPtr->GetFirstShotTime() == -1) {
				healerPtr->SetFirstShotTime(currTimeStep);
				healerPtr->SetFirstShotDelay(currTimeStep - healerPtr->GetArrvTime());
			}
		}
		else if (!freezersQ.isEmpty()) {
			Freezer* freezerPtr;
			freezersQ.dequeue(freezerPtr);
			tempFreezers.enqueue(freezerPtr);

			if (freezerPtr->GetStatus() != FRST) {
				freezerPtr->SetStatus(FRST);
				freezerPtr->SetFrstTimeFrosted(currTimeStep);
			}

			if (freezerPtr->GetFirstShotTime() == -1) {
				freezerPtr->SetFirstShotTime(currTimeStep);
				freezerPtr->SetFirstShotDelay(currTimeStep - freezerPtr->GetArrvTime());
			}
		}
		else
			break;
	}


	for (int i = 0; i < MaxEnemies; ++i) {
		if (!tempFighters.isEmpty()) {
			Fighter* ptr;
			tempFighters.dequeue(ptr);
			fightersQ.enqueuePriority(ptr->GetPriFactor(), ptr);
		}
		else if (!tempHealers.isEmpty()) {
			Healer* healerPtr;
			tempHealers.pop(healerPtr);
			healersStack.push(healerPtr);
		}
		else if (!tempFreezers.isEmpty()) {
			Freezer* freezerPtr;
			tempFreezers.dequeue(freezerPtr);
			freezersQ.enqueue(freezerPtr);
		}
		else
			break;
	}
}
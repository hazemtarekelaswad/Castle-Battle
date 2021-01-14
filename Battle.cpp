#include "Battle.h"
#include <time.h>
#include <fstream>
#include "Castle/Castle.h"
#include "Enemies/Fighter.h"
#include "Enemies/Healer.h"
#include "Enemies/Freezer.h"
Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}


Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive_Mode();
		break;
	case MODE_STEP:
		Step_Mode();
		break;
	case MODE_SLNT:
		Silent_Mode();
		break;
	/*case MODE_DEMO:
		Just_A_Demo();*/

	}

	delete pGUI;

}

void Battle::ReadFile() {
	pGUI->PrintMessage("Please Enter The File Name");
	string Filename = pGUI->GetString(); //file name to be input by the user
	ifstream Input(Filename + ".txt");

	double ch, cp;
	int n;
	Input >> ch >> n >> cp;		//castle health and maximum number of enemies hit
	EnemyCount = n;
	KilledCount = 0;
	Castle pCastle(ch, n, cp);
	this->BCastle = pCastle;
	int enemyNumber;
	Input >> enemyNumber;

	int ID, TYP, AT, H, POW, RLD, SPD;
	Enemy* pE = NULL;
	//for each enemy get the enemy's info
	for (int i = 0; i < enemyNumber; i++)
	{
		//for now we will get the id and arrival time
		Input >> ID >> TYP >> AT >> H >> POW >> RLD >> SPD;

		switch (TYP) {
		case FIGHTER:
			pE = new Fighter(ID, AT,H,POW,RLD,SPD); //add cases for each type
			break;
		case HEALER:
			pE = new Healer(ID, AT, H, POW, RLD, SPD);
			break;
		case FREEZER:
			pE = new Freezer(ID, AT, H, POW, RLD, SPD);
			break;
		}

		if (H > 0) {

			pE->SetStatus(INAC); //initiall all enemies are inactive
		}
		else {
			// then the enemy will be dead already
			pE->SetStatus(KILD);
		}
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//update the interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

}

void Battle::Silent_Mode() {
	pGUI->PrintMessage("Welcome to Silent Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount && this->GetCastle()->GetHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here
		UpdateFighters();

	}
	if (KilledCount >= EnemyCount)
		gamestatus = "WIN";
	else if (GetCastle()->GetHealth() <= 0)
		gamestatus = "LOSE";
	else
		gamestatus = "DRAWN";

}
void Battle::Interactive_Mode() {
	pGUI->PrintMessage("Welcome to Interactive Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount && this->GetCastle()->GetHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here
		UpdateFighters();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		pGUI->waitForClick();
	}

	if (KilledCount >= EnemyCount)
		gamestatus = "WIN";
	else if (GetCastle()->GetHealth() <= 0)
		gamestatus = "LOSE";
	else
		gamestatus = "DRAWN";
}
void Battle::Step_Mode() {
	pGUI->PrintMessage("Welcome to Step Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount && this->GetCastle()->GetHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here
		UpdateFighters();

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(1000);
	}

	if (KilledCount >= EnemyCount)
		gamestatus = "WIN";
	else if (GetCastle()->GetHealth() <= 0)
		gamestatus = "LOSE";
	else
		gamestatus = "DRAWN";
}

/*
//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{

	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	//
	// THIS IS JUST A DEMO Function
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	//

	srand(time(NULL));
	int Enemy_id = 0;
	int ArrivalTime = 1;
	Enemy* pE = NULL;
	//Create Random enemies and add them all to inactive queue
	for (int i = 0; i < EnemyCount; i++)
	{
		ArrivalTime += (rand() % 3);	//Randomize arrival time

		// pE = new Enemy(++Enemy_id, ArrivalTime);
		switch (TYP) {
		case FIGHTER:
			pE = new Fighter(++Enemy_id, ArrivalTime); //add cases for each type
		case HEALER:
			pE = new Healer(++Enemy_id, ArrivalTime);
		case FREEZER:
			pE = new Freezer(++Enemy_id, ArrivalTime);
		}

		pE->SetStatus(INAC); //initiall all enemies are inactive
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}

	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}
}
*/

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyListInactive = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyListInactive[i]);

	//Add other lists to drawing list
	int ActiveFreezersCount;
	Freezer* const * EnemyListActiveFreezers = Q_ActiveFreezers.toArray(ActiveFreezersCount);
	for (int i = 0; i < ActiveFreezersCount; i++) {
		pGUI->AddToDrawingList(EnemyListActiveFreezers[i]);
	}

	int KilledCount;
	Enemy* const * EnemyListKilled = Q_Killed.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++) {
		pGUI->AddToDrawingList(EnemyListKilled[i]);
	}

	int ActiveFightersCount;
	Fighter* const * EnemyListActiveFighters = PQ_ActiveFighters.toArray(ActiveFightersCount);
	for (int i = 0; i < ActiveFightersCount; i++) {
		pGUI->AddToDrawingList(EnemyListActiveFighters[i]);
	}

	int FrozenCount;
	Enemy* const * EnemyListFrozen = PQ_Frozen.toArray(FrozenCount);
	for (int i = 0; i < FrozenCount; i++) {
		pGUI->AddToDrawingList(EnemyListFrozen[i]);
	}

	int ActiveHealersCount;
	Healer* const * EnemyListHealers = S_ActiveHealers.toArray(ActiveHealersCount);
	for (int i = 0; i < ActiveHealersCount; i++) {
		pGUI->AddToDrawingList(EnemyListHealers[i]);
	}

	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	/*for (int i = 0; i < DemoListCount; i++)
		pGUI->AddToDrawingList(DemoList[i]);*/
}





//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		/*AddtoDemoList(pE);	*/	//move it to demo list (for demo purposes)
		switch (pE->GetType())		//add emeies to respective lists
		{
		case(FIGHTER):
			PQ_ActiveFighters.enqueuePriority(dynamic_cast<Fighter*>(pE)->GetPriFactor(), dynamic_cast<Fighter*>(pE));
			break;
		case(HEALER):
			S_ActiveHealers.push(dynamic_cast<Healer*>(pE));
			break;
		case(FREEZER):
			Q_ActiveFreezers.enqueue(dynamic_cast<Freezer*>(pE));
			break;
		}
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < DemoListCount; i++)
	{
		pE = DemoList[i];
		switch (pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand() % 100;
			if (Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST);
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp + KillProp))	//with kill propablity, kill some active enemies
			{
				pE->SetStatus(KILD);
				ActiveCount--;
				KilledCount++;
			}

			break;
		case FRST:
			Prop = rand() % 100;
			if (Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp + KillProp))			//with kill propablity, kill some frosted enemies
			{
				pE->SetStatus(KILD);
				FrostedCount--;
				KilledCount++;
			}

			break;
		}
	}
}

void Battle::UpdateFighters() {
	Fighter* currentFighter;
	Healer* currentHealer;
	Freezer* currentFreezer;

	//params to be printed
	bool castleFrosted = false;

	int activeFightersNum;
	PQ_ActiveFighters.toArray(activeFightersNum);
	int activeHealersNum;
	S_ActiveHealers.toArray(activeHealersNum);
	int activeFreezersNum;
	Q_ActiveFreezers.toArray(activeFreezersNum);

	int frostedFighters = 0;
	int frostedHealers = 0;
	int frostedFreezers = 0;
	int killedFighters = 0;
	int killedHealers = 0;
	int killedFreezers = 0;

	//for (int i = 0; i < EnemyCount; i++) {
		PQ_ActiveFighters.peekFront(currentFighter);	//get the first enemy from each type
		currentHealer = S_ActiveHealers.peek();
		Q_ActiveFreezers.peekFront(currentFreezer);
		//then the enemies should attack the castle
		currentFighter->Act(GetCastle(), CurrentTimeStep);
		currentFreezer->Act(GetCastle(), CurrentTimeStep);
		//then they must move forward
		currentFighter->Move();
		currentFreezer->Move();
		currentHealer->Move();
		//if the health of anyone of them is less than the full health then the healer should heal them
		if (currentFighter->GetHealth() < currentFighter->GetOrgHealth() || currentFreezer->GetHealth() < currentFreezer->GetOrgHealth()) {
			if (currentFighter->GetDistance() - currentHealer->GetDistance() <= 2) {
				currentHealer->Act(currentFighter, CurrentTimeStep);
			}
			if (currentFreezer->GetDistance() - currentHealer->GetDistance() <= 2) {
				currentHealer->Act(currentFreezer, CurrentTimeStep);
			}
		}
		//the castle should also attack enemies
		this->GetCastle()->Act(PQ_ActiveFighters, S_ActiveHealers, Q_ActiveFreezers, CurrentTimeStep);
		//this->GetCastle()->ShootBullets(PQ_ActiveFighters, S_ActiveHealers, Q_ActiveFreezers, CurrentTimeStep);
	//	this->GetCastle()->ShootIce(PQ_ActiveFighters, S_ActiveHealers, Q_ActiveFreezers, CurrentTimeStep);
		//if the health of any of the enemies is less than then move him to the killed list

		if (currentFighter->GetHealth() < 1) {
			PQ_ActiveFighters.dequeue(currentFighter);
			currentFighter->SetStatus(KILD);
			Q_Killed.enqueue(currentFighter);
			KilledCount++;

			--ActiveCount;

			killedFighters++;
			activeFightersNum--;
		}
		if (currentFreezer->GetHealth() < 1) {
			Q_ActiveFreezers.dequeue(currentFreezer);
			currentFreezer->SetStatus(KILD);
			Q_Killed.enqueue(currentFreezer);
			KilledCount++;

			--ActiveCount;
			killedFighters++;
			activeFightersNum--;

		}
		if (currentHealer->GetHealth() < 1) {
			S_ActiveHealers.pop(currentHealer);
			currentHealer->SetStatus(KILD);
			Q_Killed.enqueue(currentHealer);
			KilledCount++;

			--ActiveCount;
			killedFighters++;
			activeFightersNum--;

		}

		//check to see if any of the enemies is frozen
		if (currentHealer->Freezed()) {
			S_ActiveHealers.pop(currentHealer);
			currentHealer->SetStatus(FRST);
			PQ_Frozen.enqueuePriority(100 - currentHealer->GetFreezeTime(), currentHealer);
			FrostedCount++;

			--ActiveCount;

			frostedHealers++;
		}
		if (currentFreezer->Freezed()) {
			Q_ActiveFreezers.dequeue(currentFreezer);
			currentFreezer->SetStatus(FRST);
			PQ_Frozen.enqueuePriority(100 - currentFreezer->GetFreezeTime(), currentFreezer);
			FrostedCount++;

			--ActiveCount;
			frostedHealers++;

		}
		//then move the current time step forward
		pGUI->UpdateStatusBar(CurrentTimeStep);
		CurrentTimeStep++;
		
		if (GetCastle()->GetStatus() == 0) {
			castleFrosted = false;
		}
		else {
			castleFrosted = true;
		}
		PrintParams(GetCastle()->GetHealth(), castleFrosted, activeFightersNum, activeHealersNum, activeFreezersNum, frostedFighters, frostedHealers, frostedFreezers, killedFighters, killedHealers, killedFreezers);
	
	
	//}
}

void Battle::PrintParams(int castleHealth, bool castleFrosted, int activeFightersNum, int activeHealersNum, int activeFreezersNum, int	frostedFighters, int frostedHealers, int frostedFreezers, int killedFighters, int killedHealers, int killedFreezers) {
	castleHealth;
	castleFrosted;
	activeHealersNum;
	activeFreezersNum;
	activeFightersNum;
	int totalActiveCount = activeFightersNum + activeFreezersNum + activeHealersNum;
	frostedFighters;
	frostedFreezers;
	frostedHealers;
	int totalFrosted = frostedFighters + frostedFreezers + frostedHealers;
	killedFighters;
	killedFreezers;
	killedHealers;
	int totalKilled = killedFighters + killedFreezers + killedHealers;
}

void Battle::OutputFile()
{
	ofstream out("Outputfile.txt");


	out << "Game is " + gamestatus << endl;
	out << "KTS\tID\tFD\tKD\tLT" << endl;

	int enemy_id;
	int enemyKDS;
	int enemyFD;
	int enemyKD;
	int enemyLT;
	int totalFD = 0;
	int totalKD = 0;

	while (!Q_Killed.isEmpty())
	{
		Enemy* killed_enemy;
		Q_Killed.dequeue(killed_enemy);
		enemy_id = killed_enemy->GetID();
		enemyKDS = killed_enemy->GetEnemyKilledTime();
		enemyFD = killed_enemy->GetFirstShotDelay();
		enemyKD = killed_enemy->GetKillDelay();
		enemyLT = killed_enemy->GetLifeTime();
		totalFD += enemyFD;
		totalKD += enemyKD;

		out << enemyKDS << "\t" << enemy_id << "\t" << enemyFD << "\t" << enemyKD << "\t" << enemyLT << endl;



	}

	//////////////////////////We have to print Castle Total Damage here/////////////////////////////////

	double average_FD = (double)totalFD / EnemyCount;
	double average_KD = (double)totalKD / EnemyCount;

	if (gamestatus == "WIN")
	{
		out << "Total Enemies = " << EnemyCount << endl;

	}
	else
	{
		out << "Killed Enemies = " << KilledCount << endl;
		out << "Alive Enemies = " << EnemyCount - KilledCount << endl;
	}

	out << "Average First-Shot Delay = " << average_FD << endl;
	out << "Average Kill Delay = " << average_KD << endl;
	out.close();

}
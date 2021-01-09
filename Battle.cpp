#include "Battle.h"
#include <time.h>
#include <fstream>

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
	case MODE_STEP:
		Step_Mode();
	case MODE_SLNT:
		Silent_Mode();
	case MODE_DEMO:
		Just_A_Demo();

	}

	delete pGUI;

}

void Battle::ReadFile() {
	pGUI->PrintMessage("Please Enter The File Name");
	string Filename = pGUI->GetString(); //file name to be input by the user
	ifstream Input(Filename + ".txt");
	int ch, n, cp;
	Input >> ch >> n >> cp;
	int enemyNumber;
	Input >> enemyNumber;

	int ID, TYP, AT, H, POW, RLD, SPD;
	Enemy* pE = NULL;
	//for each enemy get the enemy's info
	for (int i = 0; i < enemyNumber; i++)
	{
		//for now we will get the id and arrival time
		Input >> ID >> TYP >> AT >> H >> POW >> RLD >> SPD;
		pE = new Enemy(ID, AT);
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
}
void Battle::Interactive_Mode() {
	pGUI->PrintMessage("Welcome to Interactive Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		pGUI->waitForClick();
	}
}
void Battle::Step_Mode() {
	pGUI->PrintMessage("Welcome to Step Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(1000);
	}
}


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
		pE = new Enemy(++Enemy_id, ArrivalTime);
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
	Enemy* const * EnemyListActiveFreezers = Q_ActiveFreezers.toArray(ActiveFreezersCount);
	for (int i = 0; i < ActiveFreezersCount; i++) {
		pGUI->AddToDrawingList(EnemyListActiveFreezers[i]);
	}

	int KilledCount;
	Enemy* const * EnemyListKilled = Q_Killed.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++) {
		pGUI->AddToDrawingList(EnemyListKilled[i]);
	}

	int ActiveFightersCount;
	Enemy* const * EnemyListActiveFighters = PQ_ActiveFighters.toArray(ActiveFightersCount);
	for (int i = 0; i < ActiveFightersCount; i++) {
		pGUI->AddToDrawingList(EnemyListActiveFighters[i]);
	}

	int FrozenCount;
	Enemy* const * EnemyListFrozen = PQ_Frozen.toArray(FrozenCount);
	for (int i = 0; i < FrozenCount; i++) {
		pGUI->AddToDrawingList(EnemyListFrozen[i]);
	}

	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	for (int i = 0; i < DemoListCount; i++)
		pGUI->AddToDrawingList(DemoList[i]);
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
		AddtoDemoList(pE);		//move it to demo list (for demo purposes)
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

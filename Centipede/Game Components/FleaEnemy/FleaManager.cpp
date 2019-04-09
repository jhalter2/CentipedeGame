#include "FleaManager.h"
#include "FleaFactory.h"
#include "Flea.h"
#include "MushroomField.h"
#include "CritterSpawner.h"

FleaManager* FleaManager::ptrInstance = NULL;

void FleaManager::privMakeFlea(MushroomField* pM) {
	int rand1 = rand() % 30 + 1;
	rand1 *= 16;
	CurrentFlea = FleaFactory::CreateFlea(sf::Vector2f((float) rand1, 0.0f), pM);
	FleaAlive = true;
}

void FleaManager::privFleaDied() {
	FleaAlive = false;
	CritterSpawner::CanSpawnFlea(true);
	CurrentFlea = 0;
}

bool FleaManager::privIsFleaAlive() {
	return FleaAlive;
}

Flea* FleaManager::privGetFlea() {
	return CurrentFlea;
}

void FleaManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

#include "ScorpionManager.h"
#include "ScorpionFactory.h"
#include "Scorpion.h"
#include "MushroomField.h"
#include "CritterSpawner.h"

ScorpionManager* ScorpionManager::ptrInstance = NULL;

void ScorpionManager::privMakeScorpion(MushroomField* pM) {
	int rand1 = rand() % 24 + 1;
	int rand2 = rand() % 2;
	//come in on left of screen
	if (rand2 == 0) {
		CurrentScorpion = ScorpionFactory::CreateScorpion(sf::Vector2f(0.0f, (float)(rand1 * 16)), pM, 2.0f, -1.0f);
	}
	//come in on right of screen
	else {
		CurrentScorpion = ScorpionFactory::CreateScorpion(sf::Vector2f(WindowManager::MainWindow.getView().getSize().x, (float)(rand1 * 16)), pM, -2.0f, 1.0f);
	}
	ScorpionAlive = true;
}

void ScorpionManager::privScorpionDied() {
	ScorpionAlive = false;
	CritterSpawner::CanSpawnScorp(true);
	CurrentScorpion = 0;
}

bool ScorpionManager::privIsScorpionAlive() {
	return ScorpionAlive;
}

Scorpion* ScorpionManager::privGetScorpion() {
	return CurrentScorpion;
}

void ScorpionManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
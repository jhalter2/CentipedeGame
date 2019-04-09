#include "CentipedeManager.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeBodyFactory.h"
#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "MushroomField.h"
#include "CritterSpawner.h"

CentipedeManager* CentipedeManager::ptrInstance = NULL;

CentipedeManager::CentipedeManager() {
	NumCentHeads = 0;
}

CentipedeHead* CentipedeManager::privMakeCentipedeHead(sf::Vector2f p, MushroomField* pM, float s, float c, int b) {
	CentipedeHead* ch = CentipedeHeadFactory::CreateCentipedeHead(p, pM, s, c, b);
	for (int i = 0; i < 20; i++) {
		if (Heads[i] == 0) {
			Heads[i] = ch;
			break;
		}
	}
	NumCentHeads++;
	return ch;
}

CentipedeBody* CentipedeManager::privMakeCentipedeBody(CentipedeHead* ch, CentipedeBody* cb1, CentipedeBody* cb2) {
	return CentipedeBodyFactory::CreateCentipedeBody(ch, cb1, cb2);
}

void CentipedeManager::privCentipedeHeadDied(CentipedeHead* pHead) {
	for (int i = 0; i < 20; i++) {
		if (Heads[i] == pHead) {
			Heads[i] = 0;
			break;
		}
	}
	NumCentHeads--;
	if (NumCentHeads == 0) privNotifyLevelChange();
}

void CentipedeManager::privRemoveCentipedeHead(CentipedeHead* pHead) {
	for (int i = 0; i < 20; i++) {
		if (Heads[i] == pHead) {
			Heads[i] = 0;
			break;
		}
	}
	NumCentHeads--;
}
void CentipedeManager::privNotifyLevelChange() {
	CritterSpawner::SpawnNextWave();
}

void CentipedeManager::privResetCentipede() {
	for (int i = 0; i < 20; i++) {
		if(Heads[i] != 0) Heads[i]->DeathReset();
	}
}

int CentipedeManager::privGetNumHeads() {
	return NumCentHeads;
}

void CentipedeManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
#include "CritterSpawner.h"
#include "Scorpion.h"
#include "Spider.h"
#include "Flea.h"
#include "MushroomField.h"
#include "FleaFactory.h"
#include "CentipedeBody.h"
#include "CentipedeHead.h"
#include "PlayerManager.h"
#include "SpiderManager.h"
#include "CentipedeManager.h"
#include "FleaManager.h"
#include "ScorpionManager.h"
#include <fstream>

//wave manager
CritterSpawner* CritterSpawner::ptrInstance = NULL;

void CritterSpawner::privGetWaveInfo() {
	using namespace std;
	FirstWave = true;
	TriggerFleaNow = false;
	PlayerAreaMushrooms = 0;
	CurrentPlayer = 0;
	arrayX = 0;
	wave = 0;
	string line;
	int convert = 0;
	string::size_type n;
	ifstream myfile("WaveInformation.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//set wave(array) number to correct wave information
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			n = line.find("wave");
			if (n != string::npos) {
				convert = line[5] - '0';
				arrayX = convert - 1;
			}
			n = line.find("centipedelength");
			if (n != string::npos) {
				convert = line[n + 16] - '0';
				WaveOptions[arrayX][0] = convert;
			}
			n = line.find("centipedespeed");
			if (n != string::npos) {
				convert = line[n + 15] - '0';
				WaveOptions[arrayX][1] = convert;
			}
			n = line.find("centipedesoloheadcount");
			if (n != string::npos) {
				convert = line[n + 23] - '0';
				WaveOptions[arrayX][2] = convert;
			}
			n = line.find("centipedesoloheadspeed");
			if (n != string::npos) {
				convert = line[n + 23] - '0';
				WaveOptions[arrayX][3] = convert;
			}
			n = line.find("fleatriggervalue");
			if (n != string::npos) {
				convert = line[n + 17] - '0';
				WaveOptions[arrayX][5] = convert;
			}
			n = line.find("flea");
			if (n != string::npos && line.find("fleatriggervalue") == string::npos) {
				convert = line[n + 5] - '0';
				WaveOptions[arrayX][4] = convert;
			}
			n = line.find("scorpionfrequency");
			if (n != string::npos) {
				convert = line[n + 18] - '0';
				WaveOptions[arrayX][7] = convert;
			}
			n = line.find("scorpion");
			if (n != string::npos  && line.find("scorpionfrequency") == string::npos) {
				convert = line[n + 9] - '0';
				WaveOptions[arrayX][6] = convert;
			}
			n = line.find("spiderfrequency");
			if (n != string::npos) {
				convert = line[n + 16] - '0';
				WaveOptions[arrayX][9] = convert;
			}
			n = line.find("spiderspeed");
			if (n != string::npos) {
				convert = line[n + 12] - '0';
				WaveOptions[arrayX][10] = convert;
			}
			n = line.find("spider");
			if (n != string::npos && line.find("spiderfrequency") == string::npos && line.find("spiderspeed") == string::npos) {
				convert = line[n + 7] - '0';
				WaveOptions[arrayX][8] = convert;
			}	
		}
		myfile.close();
	}
	privLoadCurrentWaveInfo();
}

void CritterSpawner::privLoadCurrentWaveInfo() {
	CurrentPlayer = 0;
	CritterSpawner::CancelAlarms();
	if (PlayerWaves[CurrentPlayer] == 0) FirstWave = true;
	length = WaveOptions[PlayerWaves[CurrentPlayer]][0];
	CentiSpeed = (float)WaveOptions[PlayerWaves[CurrentPlayer]][1];
	SoloHeadCount = WaveOptions[PlayerWaves[CurrentPlayer]][2];
	SoloHeadSpeed = (float)WaveOptions[PlayerWaves[CurrentPlayer]][3];
	if (WaveOptions[PlayerWaves[CurrentPlayer]][4] == 73) SpawnFlea = true;
	else SpawnFlea = false;
	FleaTrigger = WaveOptions[PlayerWaves[CurrentPlayer]][5];
	if (WaveOptions[PlayerWaves[CurrentPlayer]][6] == 73) SpawnScorpion = true;
	else SpawnScorpion = false;
	ScorpFreq = (float)WaveOptions[PlayerWaves[CurrentPlayer]][7];
	if (WaveOptions[PlayerWaves[CurrentPlayer]][8] == 73) SpawnSpider = true;
	else SpawnSpider = false;
	SpiderFreq = (float)WaveOptions[PlayerWaves[CurrentPlayer]][9];
	SpiderSpeed = (float)WaveOptions[PlayerWaves[CurrentPlayer]][10];

	if (FirstWave == true) {
	SpawnCentipede(length, CentiSpeed, 0, 0);
	if (SpawnScorpion == true) SetAlarm(1, ScorpFreq);
	if (SpawnSpider == true) SetAlarm(2, SpiderFreq);
	if (SpawnFlea == true) SetAlarm(3, FleaFreq);
	FirstWave = false;
	}
	else {
		pM->RegenShrooms();
		SetAlarm(4, Regen_delay);
	}
}

void CritterSpawner::privLoadP2WaveInfo() {
	CurrentPlayer = 1;
	CritterSpawner::CancelAlarms();
	if (PlayerWaves[CurrentPlayer] == 0) FirstWave = true;
	length = WaveOptions[PlayerWaves[CurrentPlayer]][0];
	CentiSpeed = (float)WaveOptions[PlayerWaves[CurrentPlayer]][1];
	SoloHeadCount = WaveOptions[PlayerWaves[CurrentPlayer]][2];
	SoloHeadSpeed = (float)WaveOptions[PlayerWaves[CurrentPlayer]][3];
	if (WaveOptions[PlayerWaves[CurrentPlayer]][4] == 73) SpawnFlea = true;
	else SpawnFlea = false;
	FleaTrigger = WaveOptions[PlayerWaves[CurrentPlayer]][5];
	if (WaveOptions[PlayerWaves[CurrentPlayer]][6] == 73) SpawnScorpion = true;
	else SpawnScorpion = false;
	ScorpFreq = (float)WaveOptions[PlayerWaves[CurrentPlayer]][7];
	if (WaveOptions[PlayerWaves[CurrentPlayer]][8] == 73) SpawnSpider = true;
	else SpawnSpider = false;
	SpiderFreq = (float)WaveOptions[PlayerWaves[CurrentPlayer]][9];
	SpiderSpeed = (float)WaveOptions[PlayerWaves[CurrentPlayer]][10];

	if (FirstWave == true) {
		SpawnCentipede(length, CentiSpeed, 0, 0);
		if (SpawnScorpion == true) SetAlarm(1, ScorpFreq);
		if (SpawnSpider == true) SetAlarm(2, SpiderFreq);
		if (SpawnFlea == true) SetAlarm(3, FleaFreq);
		FirstWave = false;
	}
	else {
		pM->RegenShrooms();
		SetAlarm(4, Regen_delay);
	}
}

void CritterSpawner::privIncrementWave() {
	PlayerWaves[CurrentPlayer] += 1;
	if (PlayerWaves[CurrentPlayer] == 6) PlayerWaves[CurrentPlayer] = 0;
}

void CritterSpawner::privCanSpawnFlea(bool can) {
	SpawnFlea = can;
}

void CritterSpawner::privCanSpawnScorp(bool can) {
	SpawnScorpion = can;
}

void CritterSpawner::privCanSpawnSpider(bool can) {
	SpawnSpider = can;
}

void CritterSpawner::StartSpawnScorpion(bool OnOff, float frequency) {
	SpawnScorpion = OnOff;
	ScorpFreq = frequency;
}

void CritterSpawner::StartSpawnSpider(bool OnOff, float frequency, float s) {
	SpawnSpider = OnOff;
	SpiderFreq = frequency;
	SpiderSpeed = s;
}

void CritterSpawner::StartSpawnFlea(bool OnOff, int ShroomTrigger) {
	SpawnFlea = OnOff;
	ShroomValue = ShroomTrigger;
}

void CritterSpawner::Alarm1() {
	if (SpawnScorpion) {
		ScorpionManager::MakeScorpion(pM);
		SpawnScorpion = false;
	}
	SetAlarm(1, ScorpFreq);
}

void CritterSpawner::Alarm2() {
	if (SpawnSpider) {
		SpiderManager::MakeSpider(pM, SpiderSpeed);
		SpawnSpider = false;
	}
	SetAlarm(2, SpiderFreq);
}

void CritterSpawner::Alarm3() {
	if (SpawnFlea && TriggerFleaNow) {
		FleaManager::MakeFlea(pM);
		SpawnFlea = false;
	}
	SetAlarm(3, FleaFreq);
}

void CritterSpawner::SpawnCentipede(int length, float speed, int SoloHead, int SoloHeadSpeed) {
	CentipedeHead* ch = CentipedeManager::MakeCentipedeHead(SpawnCenter, pM, CentiSpeed, centipede_column, length);
	SpawnCentipedeBody(ch, length);
}

void CritterSpawner::SpawnCentipedeBody(CentipedeHead* pHead, int count) {
	if (count > 0) {
		CentipedeBody* cb1 = CentipedeManager::MakeCentipedeBody(pHead, 0, 0);
		pHead->SetNext(cb1);
		//pointers for fixing next and prev on the bodies we will create
		CentipedeBody* pTemp = cb1;
		CentipedeBody* pFix;
		for (int i = 1; i < count; i++) {
			pFix = CentipedeManager::MakeCentipedeBody(pHead, 0, 0);
			pTemp->SetNext(pFix);
			pFix->SetPrev(pTemp);
			pTemp = pFix;
		}
	}
}

void CritterSpawner::SpawnSoloHeads(int count, float speed) {
	int rand1;
	int NewColumn;
	while (count > 0) {
		rand1 = rand() % 28 + 2;
		sf::Vector2f Position = sf::Vector2f((float)(rand1 * cell_size), SpawnCenter.y);
		NewColumn = (int)(Position.x / 16);
		CentipedeManager::MakeCentipedeHead(Position, pM, speed, (float)NewColumn, 0);
		count--;
	}
}

void CritterSpawner::privChangeCurrentPlayer() {
	if (CurrentPlayer == 0) CurrentPlayer = 1;
	else CurrentPlayer = 0;
}

void CritterSpawner::privCancelAlarms() {
	AlarmCancel(1);
	AlarmCancel(2);
	AlarmCancel(3);
}

void CritterSpawner::privRestartAlarms() {
	if (SpawnScorpion == true) SetAlarm(1, ScorpFreq);
	if (SpawnSpider == true) SetAlarm(2, SpiderFreq);
	if (SpawnFlea == true) SetAlarm(3, FleaFreq);
}

void CritterSpawner::privSetField(MushroomField* pF) {
	pM = pF;
}

void CritterSpawner::privShroomChange(int num) {
	PlayerAreaMushrooms = num;
	if (PlayerAreaMushrooms <= FleaTrigger && SpawnFlea == true) TriggerFleaNow = true;
	else TriggerFleaNow = false;
}

void CritterSpawner::privClearField() {
	//clear all critters when player dies

	if (SpiderManager::IsSpiderAlive()) SpiderManager::GetSpider()->FieldClear();
	if (ScorpionManager::IsScorpionAlive()) ScorpionManager::GetScorpion()->FieldClear();
	if (FleaManager::IsFleaAlive()) FleaManager::GetFlea()->FieldClear();
	CentipedeManager::ResetCentipede();
	SetAlarm(4, Regen_delay);
}

void CritterSpawner::privClearExtraCritters() {
	//clear left over critters once centipede is destroyed
	if (SpiderManager::IsSpiderAlive()) SpiderManager::GetSpider()->FieldClear();
	if (ScorpionManager::IsScorpionAlive()) ScorpionManager::GetScorpion()->FieldClear();
	if (FleaManager::IsFleaAlive()) FleaManager::GetFlea()->FieldClear();
	CentipedeManager::ResetCentipede();
}

//alarms to delay respawn during mushroom regen
void CritterSpawner::Alarm4() {
	//CritterSpawner::LoadCurrentWaveInfo();
	SpawnCentipede(length, CentiSpeed, 0, 0);
	SpawnSoloHeads(SoloHeadCount, SoloHeadSpeed);
	if (SpawnScorpion == true) SetAlarm(1, ScorpFreq);
	if (SpawnSpider == true) SetAlarm(2, SpiderFreq);
	if (SpawnFlea == true) SetAlarm(3, FleaFreq);
}

void CritterSpawner::privSpawnNextWave() {
	CritterSpawner::ClearExtraCritters();
	CritterSpawner::IncrementWave();
	CritterSpawner::LoadCurrentWaveInfo();
}

void CritterSpawner::Terminate()
{
	//don't need delete since it's a game object and teal cleans it up
	//delete ptrInstance;
	ptrInstance = nullptr;
}
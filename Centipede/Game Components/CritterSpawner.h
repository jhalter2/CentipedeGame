#ifndef _CritterSpawner
#define _CritterSpawner

#include "TEAL\CommonElements.h"

class Spider;
class Scorpion;
class Flea;
class MushroomField;
class CentipedeHead;

class CritterSpawner : public GameObject{
private:
	static CritterSpawner* ptrInstance;

	CritterSpawner() = default;												// Private constructor
	CritterSpawner(const CritterSpawner&) = delete;				// Prevent copy-construction
	CritterSpawner& operator=(const CritterSpawner&) = delete;	// Prevent assignment
	
	static CritterSpawner& Instance()							// Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new CritterSpawner;
		return *ptrInstance;
	};

	//get wave info from text
	void privGetWaveInfo();
	void privLoadCurrentWaveInfo();
	void privLoadP2WaveInfo();
	void privIncrementWave();
	//spawn a critter
	void StartSpawnScorpion(bool OnOff, float frequency);
	void StartSpawnSpider(bool OnOff, float frequency, float s);
	void StartSpawnFlea(bool OnOff, int ShroomTrigger);
	void SpawnCentipede(int length, float speed, int SoloHead, int SoloHeadSpeed);
	void SpawnCentipedeBody(CentipedeHead* pHead, int count);
	void SpawnSoloHeads(int count, float speed);
	//turn spawning on/off
	void privCanSpawnFlea(bool can);
	void privCanSpawnScorp(bool can);
	void privCanSpawnSpider(bool can);

	void privSpawnNextWave();

	//2p mode control
	void privChangeCurrentPlayer();
	//alarm timer for spawning scorpion = 1, and spider = 2, flea = 3
	void Alarm1();
	void Alarm2();
	void Alarm3();
	
	void privRestartAlarms();
	void privCancelAlarms();

	void privSetField(MushroomField* pF);
	//shroom in player area dies  
	void privShroomChange(int num);
	//clear enemies after player dies
	void privClearField();
	//alarm to delay respawn during mushroom regen for clear field
	void Alarm4();
	//clear enemies after last centipede head dies
	void privClearExtraCritters();

	MushroomField* pM;

	const sf::Vector2f SpawnCenter = (sf::Vector2f(WindowManager::MainWindow.getView().getSize().x / 2.0f - 8.0f, WindowManager::MainWindow.getView().getSize().y - 504.0f));

	//which wave each player is on
	int PlayerWaves[2] = { 0 };
	int CurrentPlayer;
	//track which wave array to put info into
	int arrayX;
	//wave number
	int wave;
	//for determining random spawn locations
	int rand1;
	int rand2;

	//store data for up to 21 waves that we read in from our file
	int WaveOptions[20][11] = { 0 };
	//body length of centipede
	int length;
	//value of shroom count to spawn flea
	int ShroomValue;
	//how many solo heads
	int SoloHeadCount;
	//flea trigger value
	int FleaTrigger;
	int PlayerAreaMushrooms;

	//move speeds of critters
	float CentiSpeed;
	float ExtraHeadSpeed;
	float SpiderSpeed;
	float SoloHeadSpeed;
	//column that main centipede head will spawn in
	const float centipede_column = 14.0f;
	//frequency of scorpion and spider
	float ScorpFreq;
	float SpiderFreq;
	const float FleaFreq = 0.1f;

	const float cell_size = 16.0f;

	const float Regen_delay = 3.0f;
	//whether critters can be spawned or not
	bool SpawnSpider;
	bool SpawnFlea;
	bool SpawnScorpion;
	bool TriggerFleaNow;
	bool FirstWave;

public:
	static void GetWaveInfo() { Instance().privGetWaveInfo(); };
	static void LoadCurrentWaveInfo() { Instance().privLoadCurrentWaveInfo(); };
	static void LoadP2WaveInfo() { Instance().privLoadP2WaveInfo(); };
	static void IncrementWave() { Instance().privIncrementWave(); };
	static void CanSpawnFlea(bool can) { Instance().privCanSpawnFlea(can); };
	static void CanSpawnScorp(bool can) { Instance().privCanSpawnScorp(can); };
	static void CanSpawnSpider(bool can) { Instance().privCanSpawnSpider(can); };
	static void ChangeCurrentPlayer() { Instance().privChangeCurrentPlayer(); };
	static void RestartAlarms () { Instance().privRestartAlarms(); };
	static void CancelAlarms() { Instance().privCancelAlarms(); };
	static void SetField(MushroomField* pF) { Instance().privSetField(pF); };
	static void ShroomChange(int num) { Instance().privShroomChange(num); };
	static void ClearField() { Instance().privClearField(); };
	static void ClearExtraCritters() { Instance().privClearExtraCritters(); };
	static void SpawnNextWave() { Instance().privSpawnNextWave(); };
	static void Terminate();
};

#endif _CritterSpawner;
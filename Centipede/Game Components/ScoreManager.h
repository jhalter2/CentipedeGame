#ifndef _ScoreManager
#define _ScoreManager

#include <queue>
#include "TEAL\CommonElements.h"

class CmdScore;
class DisplayText;

class ScoreManager
{
private:
	static ScoreManager* ptrInstance;

	ScoreManager() = default;												// Private constructor
	ScoreManager(const ScoreManager&) = delete;				// Prevent copy-construction
	ScoreManager& operator=(const ScoreManager&) = delete;	// Prevent assignment
	~ScoreManager();														// Only this class can delete

	// Score values;
	static const int FleaDeath = 200;
	static const int ScorpionDeath = 1000;
	static const int MushroomDeath = 1;
	static const int MushroomPoisonDeath = 1;
	static const int MushroomRegen = 5;
	static const int SpiderDeathFar = 900;
	static const int SpiderDistFar = 9999;

	static const int SpiderDeathMedium = 600;
	static const int SpiderDistMedium = 99;

	static const int SpiderDeathNear = 300;
	static const int SpiderDistNear = 9;

	static const int CentipedeBodyDeath = 10;
	static const int CentipedeHeadDeath = 100;

	std::queue<CmdScore*> QueueCmds;

	static ScoreManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new ScoreManager;
		return *ptrInstance;
	};

	void privProcessScore();
	void privSetPlayer(int p);
	void privAddScore(int val);
	void privSetDisplay(DisplayText* NewHud);
	DisplayText* privGetDisplay();
	int privGetScore(int p);

	int PlayerScores[3] = { 0 };
	int CurrentPlayerIndex = 0;
	DisplayText* hud;

public:
	// events
	enum class ScoreEvents { FleaKilled, ScorpionKilled, MushroomKilled, MushroomPoisonKilled, MushroomRegen, SpiderKilled, CentipedeBodyKilled, CentipedeHeadKilled };

	static void AddScore(int val) { Instance().privAddScore(val); };
	static void SetPlayer(int p) { Instance().privSetPlayer(p); };
	static int GetScore(int p) { return Instance().privGetScore(p); };
	static CmdScore* GetScoreCommand(ScoreEvents ev);
	static void SetDisplay(DisplayText* NewHud) { Instance().privSetDisplay(NewHud); };
	static DisplayText* GetDisplay() { return Instance().privGetDisplay(); };
	
	static void SendScoreCmd(CmdScore* c);
	static void ProcessScores();

	static void Terminate();

};
#endif _ScoreManager


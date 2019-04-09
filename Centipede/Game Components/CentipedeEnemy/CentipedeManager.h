#ifndef _CentipedeManager
#define _CentipedeManager
#include "TEAL\CommonElements.h"

class CentipedeHead;
class CentipedeBody;
class MushroomField;
class CentipedeHeadFactory;
class CentipedeBodyFactory;
class CritterSpawner;

class CentipedeManager {
private:
	static CentipedeManager* ptrInstance;

	CentipedeManager();												// Private constructor
	CentipedeManager(const CentipedeManager&) = delete;				// Prevent copy-construction
	CentipedeManager& operator=(const CentipedeManager&) = delete;	// Prevent assignment

	static CentipedeManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new CentipedeManager;
		return *ptrInstance;
	};

	CentipedeHead* privMakeCentipedeHead(sf::Vector2f p, MushroomField* pM, float s, float c, int b);
	CentipedeBody* privMakeCentipedeBody(CentipedeHead* ch, CentipedeBody* cb1, CentipedeBody* cb2);
	void privCentipedeHeadDied(CentipedeHead* pHead);
	//for clearing when player dies
	void privRemoveCentipedeHead(CentipedeHead* pHead);
	//when centipede head count = 0, notify critter spawner (wave manager)
	void privNotifyLevelChange();
	//reset centipede when player dies
	void privResetCentipede();
	//count number of heads to know when to switch waves
	int privGetNumHeads();
	int NumCentHeads;
	//pointer to wave manager for wave switch
	CritterSpawner* WaveManager;

	CentipedeHead* Heads[20] = { 0 };
public:
	static CentipedeHead* MakeCentipedeHead(sf::Vector2f p, MushroomField* pM, float s, float c, int b) { return Instance().privMakeCentipedeHead(p, pM, s, c, b); };
	static CentipedeBody* MakeCentipedeBody(CentipedeHead* ch, CentipedeBody* cb1, CentipedeBody* cb2) { return Instance().privMakeCentipedeBody(ch, cb1, cb2); };
	static void CentipedeHeadDied(CentipedeHead* pHead) { Instance().privCentipedeHeadDied(pHead); };
	static void RemoveCentipedeHead(CentipedeHead* pHead) { Instance().privRemoveCentipedeHead(pHead); };
	static void NotifyLevelChange() { Instance().privNotifyLevelChange(); };
	static void ResetCentipede() { Instance().privResetCentipede(); };
	static int GetNumHeads() { return Instance().privGetNumHeads(); };
	static void Terminate();
};
#endif _CentipedeManager

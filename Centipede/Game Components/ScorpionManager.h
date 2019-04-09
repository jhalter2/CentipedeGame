#ifndef _ScorpionManager
#define _ScorpionManager
#include "TEAL\CommonElements.h"

class Scorpion;
class MushroomField;
class ScorpionFactory;

class ScorpionManager {
private:
	static ScorpionManager* ptrInstance;

	ScorpionManager() = default;												// Private constructor
	ScorpionManager(const ScorpionManager&) = delete;				// Prevent copy-construction
	ScorpionManager& operator=(const ScorpionManager&) = delete;	// Prevent assignment

	static ScorpionManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new ScorpionManager;
		return *ptrInstance;
	};

	void privMakeScorpion(MushroomField* pM);
	void privScorpionDied();
	bool privIsScorpionAlive();

	Scorpion* privGetScorpion();
	Scorpion* CurrentScorpion;
	bool ScorpionAlive = false;
public:
	static void MakeScorpion(MushroomField* pM) { Instance().privMakeScorpion(pM); };
	static void ScorpionDied() { Instance().privScorpionDied(); };
	static bool IsScorpionAlive() { return Instance().privIsScorpionAlive(); };
	static Scorpion* GetScorpion() { return Instance().privGetScorpion(); };
	static void Terminate();
};
#endif _ScorpionManager


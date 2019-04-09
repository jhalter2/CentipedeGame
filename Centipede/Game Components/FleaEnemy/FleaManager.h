#ifndef _FleaManager
#define _FleaManager
#include "TEAL\CommonElements.h"

class Flea;
class MushroomField;
class FleaFactory;

class FleaManager {
private:
	static FleaManager* ptrInstance;

	FleaManager() = default;				// Private constructor
	FleaManager(const FleaManager&) = delete;		// Prevent copy-construction
	FleaManager& operator=(const FleaManager&) = delete;	// Prevent assignment

	static FleaManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new FleaManager;
		return *ptrInstance;
	};

	void privMakeFlea(MushroomField* pM);
	void privFleaDied();
	bool privIsFleaAlive();
	Flea* privGetFlea();

	Flea* CurrentFlea;
	bool FleaAlive = false;
public:
	static void MakeFlea(MushroomField* pM) { Instance().privMakeFlea(pM); };
	static void FleaDied() { Instance().privFleaDied(); };
	static bool IsFleaAlive() { return Instance().privIsFleaAlive(); };
	static Flea* GetFlea() { return Instance().privGetFlea(); };
	static void Terminate();
};
#endif _FleaManager

